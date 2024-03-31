create or replace procedure PAddStudentToCourse (p_student_login STUDENT.login%type, p_course_code course.code%type, p_year STUDENTCOURSE.year%type
) as
    v_capacity integer;
    v_studentCount integer;
begin
    select CAPACITY into v_capacity from course where code = p_course_code;
    select count(*) into v_studentCount from STUDENTCOURSE where course_code = p_course_code and year = p_year;

    if v_capacity >  v_studentCount then
        insert into STUDENTCOURSE (student_login, course_code, year)  values (p_student_login, p_course_code, p_year);
    else
        DBMS_OUTPUT.PUT_LINE('Kurz je plně obsazen');
    end if;
end;

create or replace trigger TInsertStudentCourse before insert on STUDENTCOURSE for each row
declare
    v_capacity integer;
    v_studentCount integer;
    v_ex exception;
begin
    select CAPACITY into v_capacity from course where code = :new.course_code;
    select count(*) into v_studentCount from STUDENTCOURSE where course_code = :new.course_code and year = :new.year;

    if v_capacity <= v_studentCount then
        DBMS_OUTPUT.PUT_LINE('Kapacita kurzu byla překročena.');
        raise v_ex;
    end if;

end;

insert into STUDENTCOURSE (student_login, course_code, year) values ('wil986', '420-adv-061', 2023);
insert into STUDENTCOURSE (student_login, course_code, year) values ('joh357', '420-adv-061', 2023);
insert into STUDENTCOURSE (student_login, course_code, year) values ('smi324', '420-adv-061', 2023);
insert into STUDENTCOURSE (student_login, course_code, year) values ('bro654', '420-adv-061', 2023);
insert into STUDENTCOURSE (student_login, course_code, year) values ('rin766', '420-adv-061', 2023);
insert into STUDENTCOURSE (student_login, course_code, year) values ('mcc676', '420-adv-061', 2023);
insert into STUDENTCOURSE (student_login, course_code, year) values ('sat767', '420-adv-061', 2023);
insert into STUDENTCOURSE (student_login, course_code, year) values ('tro552', '420-adv-061', 2023);
insert into STUDENTCOURSE (student_login, course_code, year) values ('jon067', '420-adv-061', 2023);

-- 2.3
CREATE OR REPLACE FUNCTION FGetLogin(p_lname Student.lname%TYPE) RETURN Student.login%TYPE AS
    v_studentCount INT;
BEGIN
    SELECT COUNT(*) + 1 INTO v_studentCount
    FROM Student;

    RETURN LOWER(SUBSTR(p_lname, 1, 3)) || LPAD(v_studentCount, 3, '0');
END;

-- 2.4
CREATE OR REPLACE FUNCTION FAddStudent4(p_fname Student.fname%TYPE, p_lname Student.lname%TYPE,
    p_email Student.email%TYPE, p_grade Student.grade%TYPE, p_dateOfBirth Student.date_of_birth%TYPE) RETURN VARCHAR AS

    v_login Student.login%TYPE;
    v_count integer;
BEGIN
    select count(*) into v_count from student where grade = p_grade;

    if p_grade = 1 and v_count >= 20 then
        return 'FULL';
    elsif p_grade = 2 and v_count >= 15 then
        return 'FULL';
    elsif p_grade > 2 and v_count >= 10 then
        return 'FULL';
    end if;

    v_login := FGetLogin(p_lname);

    INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
    VALUES (v_login, p_fname, p_lname, p_email, p_grade, p_dateOfBirth);

    RETURN v_login;

EXCEPTION
    WHEN OTHERS THEN
        RETURN 'error';
END;

create or replace function FLoginExists(p_login STUDENT.login%type) return string as
    v_count integer;
begin
    select count(*) into v_count from student where login = p_login;

    if v_count > 0 then
        return 'TRUE';
    else
        return 'FALSE';
    end if;
end;

create or replace function FGetNextLogin(p_lname student.lname%type) return student.login%type as
    v_prefix varchar(3);
    v_num integer;
    v_login student.login%type;
begin
    v_prefix := lower(substr(p_lname, 1, 3));
    v_num := 0;
    v_login := v_prefix || LPAD(v_num, 3, '0');

    loop
        exit when not FLoginExists(v_login);

        -- if not FLoginExists(v_login) then
        --    return v_login;
        -- end if;

        v_num := v_num + 1;
    end loop;

    return v_login;
end;

begin
    DBMS_OUTPUT.PUT_LINE(FAddStudent4('Jan', 'Gajdoš', 'jan@vsb.cz', 4, current_date));
end;

declare
    cursor c_student is select fname, lname from student;
    v_fname student.fname%type;
    v_lname student.lname%type;
begin when

    loop
        open c_student;
        exit when c_student%notfound;

        fetch c_student into v_fname, v_lname;
        DBMS_OUTPUT.PUT_LINE('student ' || v_fname || ' ' || v_lname);
    end loop;
    close c_student;
end;