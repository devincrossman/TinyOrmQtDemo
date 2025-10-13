#pragma once
#include <orm/tiny/model.hpp>
#include <orm/tiny/relations/belongsto.hpp>
#include <orm/tiny/relations/belongstomany.hpp>
#include <QDateTime>
#include <QStringList>
#include <QVariant>

#include "Models/User.h"
#include "Models/Product.h"
#include "Models/OrderProduct.h"

namespace Models
{
    class User;
    class Product;
    class Order;
    class OrderProduct;
    
    using Orm::Tiny::Model;
    using Orm::Tiny::Relations::BelongsTo;
    using Orm::Tiny::Relations::BelongsToMany;
    
    class Order : public Model<Order, User, Product, OrderProduct>
    {
        friend Model;
        using Model::Model;
    private:
        QString u_table {"orders"};
        QString u_primaryKey {"id"};

        inline static const QStringList u_fillable = {
            "user_id",
            "total"
        };

    public:
        // -------------------------------------------------------------------------
        // Relationships
        // -------------------------------------------------------------------------
        std::unique_ptr<BelongsTo<Order, User>> user()
        {
            return belongsTo<User>();
        }

        std::unique_ptr<BelongsToMany<Order, Product, OrderProduct>> products()
        {
            auto relation = belongsToMany<Product, OrderProduct>();
            relation.get()
                ->withPivot({"quantity", "price"});
            return relation;
        }

        QHash<QString, RelationVisitor> u_relations {
            {"user", [](auto &v) { v(&Order::user); }},
            {"products", [](auto &v) { v(&Order::products); }},
        };
    };
}
