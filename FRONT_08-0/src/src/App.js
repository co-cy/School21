import {useState, useEffect, useRef, useCallback} from "react";
import PokemonList from "./component/pokemonList";

function findPokemon(pokemon, curPokemonName) {
    let tmp = curPokemonName.toLowerCase();
    return pokemon.find(onePokemon => onePokemon.name.toLowerCase() === tmp);
}

function App() {
    const [pokemon, setPokemon] = useState([]);
    const [find, setFind] = useState(null);
    const [addedPokemon, setAddedPokemon] = useState([]);
    const inputText = useRef();
    console.log("APP RENDER");

    useEffect(() => {
        fetch("https://pokeapi.co/api/v2/pokemon")
            .then(res => res.json())
            .then(res => res.results)
            .then(async (res) => {
                let list_pokemon = [];
                for (let one_pokemon of res) {
                    await fetch(one_pokemon.url)
                        .then(res2 => res2.json())
                        .then(res2 => {
                            one_pokemon["info"] = res2;
                            list_pokemon.push(one_pokemon)
                        })
                }
                setPokemon(list_pokemon);
            })
    }, [])

    useEffect(() => {
        if (find) {
            setAddedPokemon(addedPokemon => [find, ...addedPokemon]);
        }
    }, [find])

    const deletePokemon = useCallback((index) => {
        let a = [...addedPokemon];
        a.splice(index, 1);
        setAddedPokemon(a);
        setFind(null);
    }, [addedPokemon]);

    const aboba = useCallback(() => {
        let a = findPokemon(pokemon, inputText.current.value);
        if (a !== find) {
            setFind(a);
        }
        }, [pokemon, find]);

    return (
        <div>
            <input ref={inputText} placeholder="Введите покемона"/>
            <button onClick={aboba}>Найти</button>
            <p>{(find === null? "": (find? "Найден" : "Не найден"))}</p>
            <PokemonList pokemon={addedPokemon} deletePokemon={deletePokemon}/>
        </div>
    );
}

export default App;
