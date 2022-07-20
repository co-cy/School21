const models = require('../../../models');

const { getIdParam } = require('../helpers');

async function getAll(req, res) {
	res.status(200).json(await models.order.findAll());
}

async function create(req, res) {
	if (req.body.id) {
		res.status(400).send(`Bad request: ID should not be provided, since it is determined automatically by the database.`)
	} else {
		const order = await models.order.create(req.body);
		order.addMenuItems(req.body.items);
		res.status(201).end();
	}
}

async function update(req, res) {
	const id = getIdParam(req);

	if (req.body.id === id) {
		await models.order.update(req.body, {
			where: {
				id: id
			}
		});
		const order = await models.order.findByPk(id);
		if (order)
			order.setMenuItems(req.body.items)
		res.status(200).end();
	} else {
		res.status(400).send(`Bad request: param ID (${id}) does not match body ID (${req.body.id}).`);
	}
}

async function remove(req, res) {
	const id = getIdParam(req);
	await models.order.update({isActive: false}, {
		where: {
			id: id
		}
	});
	res.status(200).end();
}

module.exports = {
	getAll,
	create,
	update,
	remove,
};