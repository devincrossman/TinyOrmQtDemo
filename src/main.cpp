#include <QApplication>
#include <QFile>
#include <QDebug>
#include "MainWindow.h"
#include <orm/schema.hpp>
#include <orm/db.hpp>
#include "Models/User.h"
#include "Models/Product.h"
#include "Models/Order.h"

using Orm::Schema;
using Orm::DB;

static auto db = DB::create();

void setupDatabase()
{
    DB::addConnection({
        {"driver", "QSQLITE"},
        {"database", ":memory:"},
    }, "default");

    DB::setDefaultConnection("default");

    Schema::create("users", [](auto &table) {
        table.id();
        table.string("name");
        table.string("email");
        table.timestamps();
    });

    Schema::create("products", [](auto &table) {
        table.id();
        table.string("name");
        table.decimal("price", 8, 2);
        table.timestamps();
    });

    Schema::create("orders", [](auto &table) {
        table.id();
        table.foreignId("user_id").constrained(); 
        table.decimal("total", 10, 2);
        table.timestamps();
    });

    Schema::create("order_product", [](auto &table) {
        table.foreignId("order_id").constrained().cascadeOnDelete();
        table.foreignId("product_id").constrained().cascadeOnDelete();
        
        table.unsignedTinyInteger("quantity").defaultValue(1);
        
        table.decimal("price", 8, 2); 

        table.primary({"order_id", "product_id"});
    });

    // Seed Users
    auto user1 = Models::User::create({{"name", "Jane Doe"}, {"email", "jane.doe@example.com"}});
    auto user2 = Models::User::create({{"name", "John Smith"}, {"email", "john.smith@example.com"}});
    auto user3 = Models::User::create({{"name", "Alice Brown"}, {"email", "alice.brown@example.com"}});

    // Seed Products
    auto laptop = Models::Product::create({{"name", "Laptop"}, {"price", 1200.00}});
    auto mouse = Models::Product::create({{"name", "Wireless Mouse"}, {"price", 25.00}});
    auto keyboard = Models::Product::create({{"name", "Mechanical Keyboard"}, {"price", 85.50}});
    auto monitor = Models::Product::create({{"name", "24\" Monitor"}, {"price", 200.00}});
    auto usbCable = Models::Product::create({{"name", "USB-C Cable"}, {"price", 10.00}});

    // Seed Orders
    auto order1 = Models::Order::create({{"user_id", user1.id()}, {"total", 1250.00}});
    auto order2 = Models::Order::create({{"user_id", user2.id()}, {"total", 315.50}});

    // Seed pivot table: order_product
    order1.products()->attach(laptop.id(), {{"quantity", 1}, {"price", laptop.price()}});
    order1.products()->attach(mouse.id(), {{"quantity", 2}, {"price", mouse.price()}});

    order2.products()->attach(keyboard.id(), {{"quantity", 1}, {"price", keyboard.price()}});
    order2.products()->attach(monitor.id(), {{"quantity", 1}, {"price", monitor.price()}});
    order2.products()->attach(usbCable.id(), {{"quantity", 3}, {"price", usbCable.price()}});
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    setupDatabase();

    QFile file(":/styles/darkstyle.qss");
    if(file.open(QFile::ReadOnly)) {
        QString style = QLatin1String(file.readAll());
        app.setStyleSheet(style);
        file.close();
    } else {
        qWarning() << "Could not open stylesheet file";
    }

    MainWindow window;
    window.show();
    return app.exec();
}
