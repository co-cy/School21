import {memo} from "react";
import Pokemon from "./pokemon";

const PokemonList = memo((prop) => {
    let pokemon = prop.pokemon;
    console.log("LIST POKEMON RENDER");
    return (
        <div>
            {pokemon.map((onePokemon, index) => (
                <Pokemon key={index} le={index} deletePokemon={prop.deletePokemon} pokemon={onePokemon}/>
            ))}
        </div>
    )
});

export default PokemonList;