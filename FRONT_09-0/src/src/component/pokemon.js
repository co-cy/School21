import ThemeContext from "../context"
import {memo, useContext} from "react";

const Pokemon = memo((prop) => {
    let pokemon = prop.pokemon;
    const isLight = useContext(ThemeContext);
    console.log("POKEMON RENDER", pokemon.name);
    return (
        <div className={isLight ? "container" : "container-dark"} style={{gridTemplateColumns: "10% 70% 20%"}}>
            <img className="image" alt={pokemon.name} src={pokemon.info.sprites.front_default}/>
            <div className="test_container">
                Имя: <b>{pokemon.name}</b><br/>
                Формы ({pokemon.info.forms.length}):
                <ol>
                    {pokemon.info.forms.map(({name}, index) => (
                        <li key={index}>{name}</li>
                    ))}
                </ol>
            </div>
            <button className="button_container" onClick={() => prop.deletePokemon(prop.le)}>Удалить</button>
        </div>
    )
});

export default Pokemon;