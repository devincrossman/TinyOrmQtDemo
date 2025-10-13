#pragma once
#include <orm/tiny/model.hpp>
#include <orm/tiny/relations/hasmany.hpp>

namespace Models
{
    class Order;
    class User;
    class User : public Orm::Tiny::Model<User, Order>
    {
        friend Model;
        using Model::Model;

    private:
        QString u_table {"users"};
        QString u_primaryKey {"id"};

        inline static const QStringList u_fillable {
            "name",
            "email",
        };

    public:
        qint64 id() const { return getAttribute("id").value<qint64>(); }


    public:
        // -------------------------------------------------------------------------
        // Relationships
        // -------------------------------------------------------------------------
        std::unique_ptr<Orm::Tiny::Relations::HasMany<User, Order>>
        orders()
        {
            return hasMany<Order>();
        }

        QHash<QString, RelationVisitor> u_relations {
            {"orders", [](auto &v) { v(&User::orders); }},
        };
    };
}