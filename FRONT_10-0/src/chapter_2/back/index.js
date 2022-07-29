const express = require("express")
const app = express();

const bodyParser = require('body-parser')

const db = require("./models");

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));

app.use((req, res, next) => {
    res.append('Access-Control-Allow-Origin', ['*']);
    res.append('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE');
    res.append('Access-Control-Allow-Headers', 'Content-Type');
    next();
});

app.options("/login", async (req, res) => {
    res.status(200).json({})
})

app.post("/login", async (req, res) => {
    const user = await db.user.findOne({where: {
        login: req.body.login,
        password: req.body.password
        }
    });

    let findUser = !!user;

    if (findUser) {
        let role = await user.getRole();
        let company = await user.getCompany();
        res.status(200).json({
            "find": findUser,
            "roleId": role && role.get("id"),
            "roleName": role && role.get("name"),
            "companyId": company && company.get("id"),
            "companyName": company && company.get("name")
        });
    } else {
        res.status(200).json({
            "find": findUser
        })
    }
})

app.options("/company-signup", async (req, res) => {
    res.status(200).json({});
})

app.post("/company-signup", async (req, res) => {
    const companyId = await db.company.create({name: req.body.companyName});
    const user = await db.user.create({
        login: req.body.login,
        password: req.body.password,
    });
    const role = 1;
    user.setRole(role);
    user.setCompany(companyId);

    res.status(200).json({
        "status": true,
        "role": role
    });
})

app.options("/signup", async (req, res) => {
    res.status(200).json({});
})

app.post("/signup", async (req, res) => {
    const user = await db.user.create({
        login: req.body.login,
        password: req.body.password,
    });
    const role = 0;
    user.setRole(role);

    res.status(200).json({
        "status": true,
        "role": role
    });
})

app.options("/vacancies", async (req, res) => {
    res.status(200).json({});
})

app.get("/vacancies", async (req, res) => {
    res.status(200).json(await db.vacancy.findAll());
})

app.get("/vacancies/:id", async (req, res) => {
    res.status(200).json(await db.vacancy.findByPk(parseInt(req.params.id)));
})

app.post("/create-vacancy", async (req, res) => {
    await db.vacancy.create({
        title: req.body.title,
        description: req.body.description,
        grade: req.body.grade,
        english: req.body.english
    });

    res.status(200).json({"status": true});
})


const host = "localhost"
const port = 3000;


app.listen(port, host, async () => {
    console.log("SERVER START:\nhttps://" + host + ":" + port);
    await db.sequelize.sync({force: true});
    await db.role.create({id: 0, name: "USER"});
    await db.role.create({id: 1, name: "ADMIN"});
})
