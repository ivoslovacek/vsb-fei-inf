--select email
--from customer
--where active = 0

--select title, description
--from film
--where rating = 'G'
--order by title desc

--select *
--from payment
--where year(payment_date) >= 2006
--	and amount < 2

--select description, rating
--from film
--where rating in ('G', 'PG')

--select description, rating
--from film
--where rating not in ('G', 'PG', 'PG-13')

--select *
--from film
--where length > 50
--	and rental_duration in (3, 5)

--select *
--from film
--where length > 70
--	and (title like '%RAINBOW%' or title like 'TEXAS%')

--select title
--from film
--where description like '%And%'
--	and length between 80 nad 90
--	and rental_duration % 2 <> 0

-- the query results are order because of the use of distinct, however this trait is not guaranteed
--select distinct special_features
--from film
--where replacement_cost >= 14 and replacement_cost <= 16

--select *
--from film
--where (rental_duration < 4 or rating = 'PG')
--	and not (rental_duration < 4 and rating = 'PG')

--select *
--from  address
--where postal_code is not null

--select distinct customer_id
--from rental
--where return_date is null

--select payment_id,
--	year(payment_date) as year_of_payment,
--	month(payment_date) as month_of_payment,
--		day(payment_date) as day_of_payment
--from payment

--select *
--from film
--where len(title) != 20

--select rental_id,
--	datediff(minute, rental_date, return_Date)
--from rental
--where return_date is not null

--select concat(first_name, ' ', last_name) as full_name
--from customer
--where active = 1

--select *, coalesce(postal_code, 'prazdne')
--from address

-- zadani 21, 22
--select count(*), 
--	count(original_language_id),
--	count(distinct rating)
--from film

--select count(postal_code) as postal_code_count, count(distinct postal_code) as distinct_postal_code_count
--from address