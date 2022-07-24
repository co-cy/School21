import {useState, useEffect, useRef, memo, useCallback} from "react";

function findPokemon(pokemon, curPokemonName) {
    let tmp = curPokemonName.toLowerCase();
    return pokemon.find(onePokemon => onePokemon.name.toLowerCase() === tmp);
}

const Pokemon = memo((prop) => {
    let pokemon = prop.pokemon;
    console.log("POKEMON RENDER", pokemon.name);
    return (
        <div style={{display: "grid", gridTemplateColumns: "10% 70% 20%", borderStyle: "solid", borderWidth: "1px", "margin": "2%"}}>
            <img alt={pokemon.name} src={pokemon.info.sprites.front_default}/>
            <div>
                Имя: {pokemon.name}<br/>
                Формы ({pokemon.info.forms.length}):
                <ol>
                    {pokemon.info.forms.map(({name}, index) => (
                        <li key={index}>{name}</li>
                    ))}
                </ol>
            </div>
            <button onClick={() => prop.deletePokemon(prop.le)}>Удалить</button>
        </div>
    )
});

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

    return (
        <div>
            <input ref={inputText} placeholder="Введите покемона"/>
            <button onClick={() => setFind(findPokemon(pokemon, inputText.current.value))}>Найти</button>
            <p>{(find === null? "": (find? "Найден" : "Не найден"))}</p>
            <PokemonList pokemon={addedPokemon} deletePokemon={deletePokemon}/>
        </div>
    );
}

export default App;
