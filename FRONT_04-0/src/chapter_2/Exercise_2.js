// const abob = require("../../models/index.js");
const bodyParser = require('body-parser');

const express = require('express')
const app = express()
const port = 3000


const routes = {
	users: require('./routes/users.js'),
	orders: require('./routes/orders'),
	menuItems: require('./routes/menuItems'),
};

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));

function makeHandlerAwareOfAsyncErrors(handler) {
	return async function(req, res, next) {
		try {
			await handler(req, res);
		} catch (error) {
			next(error);
		}
	};
}

app.get('/menu',
    makeHandlerAwareOfAsyncErrors(routes.menuItems.getAll)
);

app.post('/menu',
	makeHandlerAwareOfAsyncErrors(routes.menuItems.create)
);

app.get('/order',
	makeHandlerAwareOfAsyncErrors(routes.orders.getAll)
);

app.post('/order',
    makeHandlerAwareOfAsyncErrors(routes.orders.create)
);

app.put(`/order/:id`,
    makeHandlerAwareOfAsyncErrors(routes.orders.update)
);

app.delete('/order/:id',
    makeHandlerAwareOfAsyncErrors(routes.orders.remove)
);

app.post('/waiter',
    makeHandlerAwareOfAsyncErrors(routes.users.create)
);

app.listen(port, () => {
  console.log(`Example app listening on port ${port}`)
})