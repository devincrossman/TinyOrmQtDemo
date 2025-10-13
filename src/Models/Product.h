#pragma once
#include <orm/tiny/model.hpp>
#include <orm/tiny/relations/belongstomany.hpp>
#include "Models/OrderProduct.h"

namespace Models
{
    class Product;
    class Order;
    class OrderProduct;
    using Orm::Tiny::Model;

    class Product : public Model<Product, Order, OrderProduct>
    {
        friend Model;
        using Model::Model;

    private:
        QString u_table {"products"};
        QString u_primaryKey {"id"};

        inline static const QStringList u_fillable {
            "name",
            "price",
        };
    
    public:
        qint64 id() const { return getAttribute("id").value<qint64>(); }
        double price() const { return getAttribute("price").value<double>(); }

    public:
        // -------------------------------------------------------------------------
        // Relationships
        // -------------------------------------------------------------------------
        std::unique_ptr<Orm::Tiny::Relations::BelongsToMany<Product, Order, OrderProduct>> orders()
        {
            auto relation = belongsToMany<Order, OrderProduct>();
            relation.get()
                ->withPivot({"quantity", "price"}); 
            return relation;
        }

        QHash<QString, RelationVisitor> u_relations {
            {"orders", [](auto &v) { v(&Product::orders); }},
        };
    };
}