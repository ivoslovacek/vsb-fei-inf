CREATE TABLE "Customer" (
                            "Id"	INTEGER,
                            "Name"	TEXT NOT NULL,
                            "Address"	TEXT,
                            PRIMARY KEY("Id" AUTOINCREMENT)
);

CREATE TABLE "Order" (
                         "Id"	INTEGER,
                         "CustomerId"	INTEGER NOT NULL,
                         "Product"	TEXT NOT NULL,
                         "Price"	NUMERIC NOT NULL,
                         FOREIGN KEY("CustomerId") REFERENCES "Customer"("Id"),
                         PRIMARY KEY("Id" AUTOINCREMENT)
);