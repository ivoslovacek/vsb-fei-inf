select code, name
from COURSE
join SLO0168.TEACHER T on COURSE.TEACHER_LOGIN = T.LOGIN
where T.FNAME = 'Jerry' and
      T.LNAME = 'Jordon'

select distinct STUDENT.*
from STUDENT
join SLO0168.STUDENTCOURSE S on STUDENT.LOGIN = S.STUDENT_LOGIN
join SLO0168.COURSE C2 on S.COURSE_CODE = C2.CODE
join SLO0168.TEACHER T on C2.TEACHER_LOGIN = T.LOGIN
where S.YEAR >= 2020 and s.YEAR <= 2021 and
      T.FNAME = 'Jerry' and
      T.LNAME = 'Jordon'
order by STUDENT.LNAME

select  s.FNAME, s.LNAME, (
                         select count(*) from STUDENTCOURSE
                         where s.LOGIN = STUDENTCOURSE.STUDENT_LOGIN
                         ) count
from STUDENT s
where s.EMAIL like '%@vsb.cz'


insert into TEACHER(login, fname, lname, department)
values ('Peter', 'Burton', 'bur154', 'Department of Mathematics')
--commit after inserting a new line into oracle db

update course set TEACHER_LOGIN = 'bur154' where NAME = 'Database Systems II'

delete from STUDENTCOURSE where COURSE_CODE in (
    select COURSE_CODE
    from STUDENTCOURSE
    join SLO0168.COURSE C2 on C2.CODE = STUDENTCOURSE.COURSE_CODE
    join SLO0168.TEACHER T on T.LOGIN = C2.TEACHER_LOGIN
    where T.FNAME = 'Carl' and T.LNAME = 'Artis'
    )


insert into STUDENTCOURSE(COURSE_CODE,YEAR, STUDENT_LOGIN)
select COURSE.CODE, 2021, (select STUDENT.LOGIN
                           from STUDENT
                           where FNAME = 'Barbara' and LNAME = 'Jones'
                           )
from COURSE
join SLO0168.TEACHER T on T.LOGIN = COURSE.TEACHER_LOGIN
where t.FNAME = 'Walter' and t.LNAME = 'Perryman'

update STUDENT set DATE_OF_BIRTH = to_date('2.3.1997', 'DD.MM.YYYY') where LOGIN = 'smi324'

select *
from STUDENT
where  LOGIN = 'smi324'

(select LNAME, DATE_OF_BIRTH, floor(months_between(current_date, DATE_OF_BIRTH) / 12) age
from STUDENT)

select s1.FNAME, s1.LNAME
from STUDENT s1
inner join STUDENT s2 on 1=1
where S2.FNAME = 'Michael' and s2.LNAME='Silverman' and
      (months_between(s1.DATE_OF_BIRTH, s2.DATE_OF_BIRTH) <= 3)

select upper(FNAME || ' ' || LNAME) full_name from TEACHER


