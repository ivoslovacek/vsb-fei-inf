insert into actor
values ('Arnold', 'Schwarzenegger', CURRENT_TIMESTAMP)

select *
from actor
where first_name = 'Arnold'

insert into film
values ('Terminator', 'Epic', 1990, 1, null, 6, 0,99, 130, 'PG-13', 'Deleted scenes', current_timestamp)

select *
from film
where title='terminator'

insert into film_actor
values (201, 1001, current_timestamp)

select *
from film_actor
join actor on film_actor.actor_id = actor.actor_id
where film_id = 1001

insert into film_category
values (
        (select film_id
         from film
         where  title = 'Terminator'),
        (select category_id
         from category
         where name = 'Action'),
        current_timestamp
       )

insert into film_category
select film_id, category_id, current_timestamp
from film
cross join category
where title = 'Terminator' and name in ('Sci-fi', 'Comedy')

select *
from film_category
join film on film_category.film_id = film.film_id
join category on film_category.category_id = category.category_id
where film.title = 'Terminator'

update film
set rental_rate = 2.99, last_update = current_timestamp
where title = 'Terminator'

update film
set rental_rate = rental_rate * 1.1
where film.film_id in (
    select film_id
    from film_actor
    join actor on film_actor.actor_id = actor.actor_id
    where first_name = 'ZERO' and last_name = 'CAGE'
    )

insert into inventory
select film.film_id, 2, current_timestamp
from film
join film_actor on film.film_id = film_actor.film_id
join actor on film_actor.actor_id = actor.actor_id
where actor.first_name = 'GROUCHO' and actor.last_name = 'SINATRA'

delete from film_actor
where film_id in (
    select film_id
    from film
    where title='Terminator'
    )
delete from film_category
where film_id in (
    select film_id
    from film
    where title='Terminator'
)
delete from film
where film_id in (
    select film_id
    from film
    where title='Terminator'
)

alter table film
add inventor_count int

update film
set inventor_count = (
    select count(*)
    from inventory
    where  inventory.film_id = film.film_id
    )

alter table film
drop column inventor_count

alter table category
alter column name varchar(50) not null

alter table film
add creator_staff_id tinyint null

alter table film
add constraint FK_staff foreign key(creator_staff_id)
    references staff

alter table staff
add constraint check_email
    check(email like '%@%.%')

alter table staff
drop constraint check_email

create table reservation (
    reservation_id int primary key identity,
    reservation_date date not null default current_timestamp,
    end_date date not null,
    customer_id int not null references customer,
    film_id int not null references film,
    staff_id tinyint null references staff
)

insert into reservation(end_date, customer_id, film_id)
values (current_timestamp, 1, 1)

select *
from reservation

delete from reservation
where customer_id = 1

create table reviews (
    film_id int references film,
    customer_id int references customer,
    primary key (film_id, customer_id),
    
)