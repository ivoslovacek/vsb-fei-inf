#!/bin/bash

# Start the script to create the DB and user
/bin/bash /docker-entrypoint-initdb.d/configure-db.sh &

# Start SQL Server
/opt/mssql/bin/sqlservr
