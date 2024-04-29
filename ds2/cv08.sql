create or alter function FLoginExists(@p_login char(6)) returns bit as
begin
    declare @v_exists bit = 0;

    if exists(select * from student where login = @p_login) begin
        set @v_exists = 1;
    end;

    return @v_exists;
end;

go
select dbo.FLoginExists('jaw254')
select dbo.FLoginExists('cab466')

go

create or alter function FGetNextLogin(@p_lname varchar(50)) returns char(6) as
begin
    declare @v_login char(6) = null;
    declare @v_login_number int = 0;


    while @v_login is null or dbo.FLoginExists(@v_login) = 1 begin
       set @v_login_number += 1;
       set @v_login = lower(left(@p_lname, 3) + right('00' + cast(@v_login_number as varchar(3)), 3));
    end;

    return @v_login;
end;

go

select dbo.FGetNextLogin('Slovacek');

go

create or alter procedure PAddStudent(@p_fname varchar(50), @p_lname varchar(50), @p_email varchar(50), @p_grade int,
 @p_dateOfBirth date) as
begin
    declare @v_login char(6) = dbo.FGetNextLogin(@p_lname);

    insert into dbo.Student(login, fname, lname, email, grade, date_of_birth) values (@v_login, @p_fname, @p_lname, @p_email,
                                                                                      @p_grade, @p_dateOfBirth);
end;

go

exec dbo.PAddStudent 'Ivo', 'Slováček', 'ivo.slovacek.st@vsb.cz', 2, '2003-7-30';
select dbo.FGetNextLogin('slovacek');

select * from dbo.Student
where lname = 'Slováček'

go

create or alter procedure StudentBecomeTeacher(@p_login char(6), @p_department varchar(50)) as
begin
    begin TRANSACTION;

    insert into dbo.Teacher(login, fname, lname, department) select login, fname, lname, @p_department
                                                             from Student
                                                             where login = @p_login

    delete from StudentCourse
    where student_login = @p_login;

    delete from dbo.Student
    where login = @p_login;

    commit;
end;

go

exec dbo.StudentBecomeTeacher slo001, N'FŮLJADSVHKHA'

select *
from Student
where lname = N'Slováček'

select *
from Teacher
where lname = N'Slováček'

delete from dbo.Teacher
where login = 'slo001'

go

create or alter procedure PAwardStudents (@p_year int, @p_amount money) as
begin
    begin transaction;

    declare @v_login char(6);
    declare @v_points int;

    declare c_students cursor for
        select top 5 student_login, sum(points)
        from StudentCourse
        where year = @p_year
        group by student_login
        order by sum(points) desc;

    open c_students;

    fetch c_students into @v_login, @v_points;

    while @@fetch_status = 0  begin
        print @v_login + ': ' + cast(@v_points as varchar)
        + '- ' + cast(@p_amount as varchar);

        update dbo.Student set account_balance += @p_amount where login = @v_login;

        set @p_amount /= 2;

        fetch c_students into @v_login, @v_points;
    end

    close c_students;
    deallocate c_students;

    commit;
end;

go

exec PAwardStudents '2020', 10000;

go

create or alter trigger TUpdateStudent on Student after update as
begin
    declare @v_new_lname varchar(50);
    declare @v_old_lname varchar(50);

    declare c_data cursor for
        select i.lname, d.lname from inserted  i join deleted  d
        on i.login = d.login

    open c_data;

    fetch c_data into @v_new_lname, @v_old_lname;
    while @@fetch_status = 0 begin
        print @v_old_lname + ' => ' + @v_new_lname;
        fetch c_data into @v_new_lname, @v_old_lname;
    end

    close c_data;
    deallocate c_data;
end;

go

create or alter trigger TInsertStudent on Student after insert as
begin
    
end;