set serveroutput on;

select * from USER_TABLES;

create or replace procedure PPrepareTableReward(procedure_name string) as
    table_exists integer;
begin

    select count(*) into table_exists from user_tables
    where  table_name = upper(procedure_name);

    if table_exists > 0 then
        execute immediate 'drop table ' || upper(procedure_name);
    end if;

    execute immediate 'create table ' || upper(procedure_name) || '(' ||
                      'id integer primary key,' ||
                      'student_login char(6) references student,' ||
                      'winter_reward integer null,' ||
                      'summer_reward integer null,' ||
                      'thesis_reward integer null' ||
                      ')';
end;

call PPREPARETABLEREWARD('TEST');

CREATE OR REPLACE PROCEDURE PSetStudentReward(p_login Student.login%TYPE, p_rewardType VARCHAR, p_reward INTEGER) AS
    v_id INT;
    v_sql VARCHAR(500);
BEGIN
    SELECT COALESCE(MAX(ID), 0) + 1 INTO v_id
    FROM Reward;

    v_sql := 'INSERT INTO Reward (id, student_login, ' || p_rewardType || '_reward) VALUES (:1, :2, :3)';

    EXECUTE IMMEDIATE v_sql USING v_id, p_login, p_reward;
END;

call PSETSTUDENTREWARD('smi324', 'winter', 2);

select * from STUDENT;
select * from REWARD;

create or replace procedure PUpdateGradeStatic(p_grade STUDENT.grade%type, p_fname STUDENT.fname%type, p_lname STUDENT.lname%type) as
begin
    update STUDENT set GRADE = p_grade where FNAME = p_fname and LNAME = p_lname;
end;

create or replace procedure PUpdateGradeDynamic(p_grade STUDENT.grade%type, p_fname STUDENT.fname%type, p_lname STUDENT.lname%type) as
begin
    execute immediate 'update STUDENT set GRADE = :1 where 1=1 and FNAME like ''' || coalesce(p_fname, '%') ||
                      ''' and LNAME like ''' || coalesce(p_lname, '%') || ''''
    using p_grade;
end;

call PUpdateGradeDynamic(3, null, 'Smith');

create or replace procedure PUpdateGrade(p_grade STUDENT.grade%type, p_fname STUDENT.fname%type, p_lname STUDENT.lname%type, p_type string) as
begin
    if p_type = 'static' then
        begin
            PUpdateGradeStatic(p_grade, p_fname,p_lname);
        end;
    else if p_type = 'dynamic' then
        begin
            PUpdateGradeDynamic(p_grade, p_fname, p_lname);
        end;
    end if;
    end if;
end;

    