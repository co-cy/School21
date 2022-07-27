import {memo} from "react";
import Pokemon from "./pokemon";
import {useSelector} from "react-redux"

const PokemonList = memo(() => {
    let pokemon = useSelector(state => state.value);
    console.log("LIST POKEMON RENDER");
    return (
        <div>
            {pokemon.map((onePokemon, index) => (
                <Pokemon key={index} index={index}/>
            ))}
        </div>
    )
});

export default PokemonList;