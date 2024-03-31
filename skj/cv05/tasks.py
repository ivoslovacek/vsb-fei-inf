import xml.etree.ElementTree as ET


def create_student(xml_root, student_id):
    '''
    Vytvořte studenta dle loginu.
    Ujistěte se, že student neexistuje, jinak: raise Exception('student already exists')
    '''

    students = xml_root.findall("student")

    for student in students:
        xml_student_id = student.get("student_id")
        if xml_student_id == student_id:
            raise Exception("student already exists")

    new_student = ET.Element("student", {"student_id": student_id})
    xml_root.append(new_student)


def remove_student(xml_root, student_id):
    '''
    Odstraňte studenta dle loginu
    '''

    students = xml_root.findall("student")

    for student in students:
        xml_student_id = student.get("student_id")
        if xml_student_id == student_id:
            xml_root.remove(student)


def set_task_points(xml_root, student_id, task_id, points):
    '''
    Přepište body danému studentovi u jednoho tasku
    '''

    students = xml_root.findall("student")

    for student in students:
        xml_student_id = student.get("student_id")
        if xml_student_id == student_id:

            tasks = student.findall("task")

            for task in tasks:
                if task_id == task.get("task_id"):
                    task.text = points
                    return


def create_task(xml_root, student_id, task_id, points):
    '''
    Pro daného studenta vytvořte task s body.
    Ujistěte se, že task (s task_id) u studenta neexistuje, jinak: raise Exception('task already exists')
    '''

    students = xml_root.findall("student")

    for student in students:
        xml_student_id = student.get("student_id")
        if xml_student_id == student_id:

            tasks = student.findall("task")

            for task in tasks:
                if task_id == task.get("task_id"):
                    raise Exception("task already exists")

            new_task = ET.SubElement(
                student, "task", {"task_id": task_id})
            new_task.text = points


def remove_task(xml_root, task_id):
    '''
    Napříč všemi studenty smažte task s daným task_id
    '''

    students = xml_root.findall("student")

    for student in students:
        tasks = student.findall("task")

        for task in tasks:
            if task_id == task.get("task_id"):
                student.remove(task)
