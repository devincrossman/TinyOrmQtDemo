#pragma once
#include <orm/tiny/relations/basepivot.hpp>

using Orm::Tiny::Relations::BasePivot;

namespace Models
{
    class OrderProduct final : public BasePivot<OrderProduct>
    {
        friend Model;
        friend BasePivot;

        using BasePivot::BasePivot;

        inline static const QStringList u_fillable {
                "quantity",
                "price",
            };
    };
}