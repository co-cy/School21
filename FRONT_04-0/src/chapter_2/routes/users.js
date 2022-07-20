const models = require('../../../models');

async function create(req, res) {
	if (req.body.id) {
		res.status(400).send(`Bad request: ID should not be provided, since it is determined automatically by the database.`)
	} else {
		const user = await models.user.create(req.body);
		user.addOrders(req.body.orders);
		res.status(201).end();
	}
}

module.exports = {
	create
};