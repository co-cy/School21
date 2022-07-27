import ThemeContext from "../context"
import {memo, useContext} from "react";
import {useDispatch, useSelector} from "react-redux";
import store from "../store";

const Pokemon = memo((prop) => {
    let index = prop.index;

    let pokemon = useSelector(state => state.value[index]);
    console.log("POKEMON RENDER", pokemon.name);
    const isLight = useContext(ThemeContext);

    const dispatcher = useDispatch();

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
            <button className="button_container" onClick={() => dispatcher(store.removePokemon(index))}>Удалить</button>
        </div>
    )
});

export default Pokemon;