/*

У экземпляра класса должны присутствовать св-ва:
-name string
-grade string Для простоты предположим, что система грейдов будет иметь значения от L1 до L4
-hardSkills string[]
-company string


Так же должны иметься три метода:

-changeCompany(newCompanyName) - сотрудник может сменить компанию, либо же просто уволиться
-upGrade() - сотрудник может повысить квалификацию
-addSkill(newSkillName) - сотрудник может дополнить список своих скиллов.
*/


export class Empleyee {
    constructor(name, grade, hardSkills, company) {
        this.name = name;
        if (grade === "L4" || grade === "L3" || grade === "L4" || grade === "L4")
            this.grade = grade;
        else
            this.grad = null;
        this.hardSkills = hardSkills;
        this.company = company;
    }

    changeCompany(companyName) {
        this.company = companyName
    }

    upGrade() {
        if (!this.grade) {
            this.grade = "L1";
        } else if (this.grade === "L2") {
            this.grade = 'L2';
        } else if (this.grade === "L3") {
            this.grade = 'L4';
        }
    }

    addSkill(newSkillName) {
        this.hardSkills.push(newSkillName);
    }

}