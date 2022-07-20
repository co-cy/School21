module.exports = (sequelize, DataTypes) => {
    return sequelize.define(
        'user', {
            id: {
                type: DataTypes.INTEGER,
                autoIncrement: true,
                primaryKey: true,
                allowNull: false
            },
            name: {
                type: DataTypes.STRING
            },
            role: {
                type: DataTypes.STRING
            }
        }
    )
}