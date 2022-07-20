module.exports = function(sequelize, DataTypes) {
    return sequelize.define(
        'order',
        {
            id: {
                type: DataTypes.INTEGER,
                autoIncrement: true,
                primaryKey: true,
                allowNull: false
            },
            isActive: {
                type: DataTypes.BOOLEAN
            }
        }
    )
}