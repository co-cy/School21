module.exports = function(sequelize, DataTypes) {
    return sequelize.define(
        "vacancy",
        {
            id: {
                type: DataTypes.INTEGER,
                autoIncrement: true,
                primaryKey: true,
                allowNull: false
            },
            title: {
                type: DataTypes.STRING,
            },
            description: {
                type: DataTypes.STRING,
            },
            grade: {
                type: DataTypes.INTEGER,
            },
            english: {
                type: DataTypes.STRING,
            }
        }
    )
}