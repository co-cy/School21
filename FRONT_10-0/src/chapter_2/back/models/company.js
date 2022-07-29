module.exports = function(sequelize, DataTypes) {
    return sequelize.define(
        "company",
        {
            id: {
                type: DataTypes.INTEGER,
                autoIncrement: true,
                primaryKey: true,
                allowNull: false
            },
            name: {
                type: DataTypes.STRING,
                unique: true
            },
        }
    )
}