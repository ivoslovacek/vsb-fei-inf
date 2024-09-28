FROM python:3.12

WORKDIR /app

COPY requirements.txt .
COPY Makefile .

RUN curl https://packages.microsoft.com/keys/microsoft.asc | apt-key add -
RUN echo "deb [arch=amd64] https://packages.microsoft.com/ubuntu/20.04/prod focal main" | tee /etc/apt/sources.list.d/mssql-release.list

RUN apt-get update && apt-get install -y --no-install-recommends unixodbc-dev unixodbc
RUN ACCEPT_EULA=Y apt-get install -y msodbcsql17
RUN apt-get install -y npm
RUN npm install -g less

RUN pip install -r ./requirements.txt
RUN make -j

RUN python manage.py migrate
