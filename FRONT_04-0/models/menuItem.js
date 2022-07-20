module.exports = function(sequelize, DataTypes) {
    return  sequelize.define(
        'menultem',
        {
            id: {
                type: DataTypes.INTEGER,
                autoIncrement: true,
                primaryKey: true,
                allowNull: false
            },
            title: {
                type: DataTypes.STRING
            },
            picture: {
                type: DataTypes.STRING
            },
            cost: {
                type: DataTypes.DOUBLE
            },
            callQuantity: {
                type: DataTypes.INTEGER
            },
            dascription: {
                type: DataTypes.STRING
            }
        }
    )
}