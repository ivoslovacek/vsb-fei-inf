#!/bin/bash

# Wait 60 seconds for SQL Server to start up by ensuring that 
# calling SQLCMD does not return an error code, which will ensure that sqlcmd is accessible
# and that system and user databases return "0" which means all databases are in an "online" state
# https://docs.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-databases-transact-sql?view=sql-server-2017 

DBSTATUS=1
ERRCODE=1
i=0

while [[ $DBSTATUS -ne 0 ]] && [[ $i -lt 60 ]] && [[ $ERRCODE -ne 0 ]]; do
  i=$((i+1))  # Corrected incrementing the value of i
  DBSTATUS=$(/opt/mssql-tools/bin/sqlcmd -h -1 -t 1 -U sa -P "$SA_PASSWORD" -Q "SET NOCOUNT ON; SELECT SUM(state) FROM sys.databases")
  ERRCODE=$?
  sleep 1
done

if [ $DBSTATUS -ne 0 ] || [ $ERRCODE -ne 0 ]; then  # Changed OR to ||
  echo "SQL Server took more than 60 seconds to start up or one or more databases are not in an ONLINE state"
  exit 1
fi

# Execute tables creation script
/opt/mssql-tools/bin/sqlcmd -S localhost -U sa -P "$SA_PASSWORD" -i /docker-entrypoint-initdb.d/tables_create.sql

# Check for successful execution (optional)
if [[ $? -eq 0 ]]; then
  echo "Tables created successfully!"

    # Execute table population script
      /opt/mssql-tools/bin/sqlcmd -S localhost -U sa -P "$SA_PASSWORD" -f 65001 -i /docker-entrypoint-initdb.d/tables_populate.sql

    # Check for successful execution (optional)
    if [[ $? -eq 0 ]]; then
        echo "Tables populated successfully!"
    else
        echo "Error populating tables! Check tables_populate.sql"
        exit 1  # Exit with an error code if script fails
    fi
else
  echo "Error creating tables! Check tables_create.sql"
  exit 1  # Exit with an error code if script fails
fi


echo "Database initialization complete."
