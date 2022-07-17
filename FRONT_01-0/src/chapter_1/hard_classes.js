

/* В продолжение прошлого задания вам нужно нужно создать 4 новых класса:

- Company - класс описывающий IT компанию. Состоит из:
1. Св-ва:
- companyName
- currentProjects - текущий пулл проектов. Массив экземпляров класса Project
- completedProjects - пулл завершенных проектов. Массив экземпляров класса Project
- staff - весь пулл сотрудников компании. Это объект, у которого есть поля Developers, Managers. В этих полях лежат массивы экземпляров аналогичных классов.
2. Методы:

- addNewCompanyMember() - позволяет нанять нового сотрудника. В результате метода у выбранного сотрудника

должно смениться имя компании.
- addProject() - позволяет добавить проект в пулл текущих.
- getMembersQuantity() - позволяет получить кол-во сотрудников, работающих в данной комании

- Project - класс описывающий проект компании. На проекте может быть только 1 менеджер! Каждый сотрудник может работать только над одним проектом! Состоит из:
- Project Name
- minQualification - минимальная квалификация сотрудника, для работы на данном проекте.
- Team - команда проекта. Объект, типа {Managers: [], Developers: {Frontend : [], Backend: []}}. В св-ва этого объекта указан массив аналогичных классов.

Метод:
- completeProject() - позволяет закончить проект. В результате выполнения функции проект из currentProjects перемещается в finishedProjects. У команды данного проекта должно увеличиться кол-во завершенных проектов.
- addNewProjectMember() - Метод внутри которого вызывается проверка менеджера на то, подходит ли сотрудник проекту. Если подходит, то команда расширяется, иначе нет.


- Backend Developer - Класс, который наследуется от класса Employee. Имеет новые св-ва:
- stack - Массив в котором указаны технологии, которыми владеет разработчик.
- developerSide - 'backend'
- projectQuantity - Число завершенных проектов.
- expandStack() - разработчик может увеличить стек технологий.

- Frontend Developer - Класс, который наследуется от класса Employee. Имеет новые св-ва:
- stack - Массив в котором указаны технологии, которыми владеет разработчик.
- developerSide - 'frontend'
- projectQuantity - Число завершенных проектов.
- expandStack() - разработчик может увеличить стек технологий.

-Manager - Класс, который наследуется от класса Employee. Имеет новые св-ва:
- projectQuantity - Число завершенных проектов.

- checkMember(minQuantity) - менеджер проверяет, удовлетворяет ли сотрудник условиям проекта. Сотрудник, состоящий в другой компании не может работать над проектом другой компании.

*/

import { Empleyee } from "./classes.js";

export class Company {
    constructor(companyName, currentProjects, completedProjects, staff) {
        this.companyName = companyName;
        this.currentProjects = currentProjects;
        this.completedProjects = completedProjects;
        this.staff = staff;
    }

    addProject(Project) {
        this.currentProjects.push(Project);
    }

    addNewCompanyMember(member) {
        member.changeCompany(this.companyName);

        if (member instanceof Manager) {
            this.staff["managers"].push(member);
        } else if (member in FrontendDeveloper) {
            this.staff["developers"]["frontend"].push(member);
        } else {
            this.staff["developers"]["backend"].push(member);
        }
    }

    getMembersQuantity() {
        return this.staff["managers"].length
            + this.staff["developers"]["frontend"].length
            + this.staff["developers"]["backend"].length;
    }
}


/*
- projectName - string
- minQualification -number
- Team -  {
   manager : экземпляр класса Manager
   developers: {
   frontend : массив содержащий экземпляры класса FrontendDeveloper
   backend : массив содержащий экземпляры класса DackendDeveloper
   }
}


completeProject()
addNewProjectMember(Developer/Manager) - Метод внутри которого вызывается проверка менеджера на то, подходит ли сотрудник проекту. Если подходит, то команда расширяется, иначе нет.
*/

export class Project {
    constructor(projectName, minQualification, team) {
        this.projectName = projectName;
        this.minQualification = minQualification;
        this.team = team;
    }

    completeProject() {
        this.team["manager"].projectQuantity++;
        for (let person of this.team["developers"]["fronted"])
            person.projectQuantity++;
        for (let person of this.team["developers"]["backend"])
            person.projectQuantity++;
    }

    addNewProjectMember(member) {

        if (!this.team["manager"].checkMember(this.minQualification, member))
            return;

        if (member instanceof Manager) {
            this.team["manager"] = member;
        } else if (member instanceof FrontendDeveloper) {
            this.team["developers"]["fronted"].push(member);
        } else if (member instanceof BackendDeveloper) {
            this.team["developers"]["backend"].push(member);
        }
    }
}

export class Manager extends Empleyee {
    constructor(projectQuantity, ...other) {
        super(...other);

        this.projectQuantity = projectQuantity;
    }

    checkMember(minQuantity, member) {
        if (member instanceof FrontendDeveloper) {
            return this.company === member.company && member.grade >= minQuantity;
        } else if (member instanceof  BackendDeveloper) {
            return this.company === member.company && member.grade >= minQuantity;
        }
        return false;
    }
}

export class FrontendDeveloper extends Empleyee {
    constructor(stack, developerSide, projectQuantity, ...other) {
        super(...other);

        this.stack = stack;
        this.developerSide = developerSide;
        this.projectQuantity = projectQuantity;
    }

    expandStack(someTech) {
        this.stack.push(someTech);
    }
}

export class BackendDeveloper extends Empleyee {
    constructor(stack, developerSide, projectQuantity, ...other) {
        super(...other);

        this.stack = stack;
        this.developerSide = developerSide;
        this.projectQuantity = projectQuantity;
    }

    expandStack(someTech) {
        this.stack.push(someTech);
    }
}
