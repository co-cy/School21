const db = require('../../../models');

async function getAll(req, res) {
	res.status(200).json(await db.menuItem.findAll());
}

async function create(req, res) {
	if (req.body.id) {
		res.status(400).send(`Bad request: ID should not be provided, since it is determined automatically by the database.`)
	} else {
		await db.menuItem.create(req.body);
		res.status(201).end();
	}
}

module.exports = {
	getAll,
	create
};