import * as fs from 'fs';


export const progressbar = async () => {

    let dir = "files/fsHard/";

    let files =  await fs.promises.readdir(dir);

    let all_size = 0;
    let list_pomises = [];
    for (let file of files) {
        let promise = fs.promises.stat(dir + file);
        promise.then((res) => {
            all_size += res.size;
        })
        list_pomises.push(promise);
    }

    let cur_size = 0;
    Promise.allSettled(list_pomises).then((promise) => {
        list_pomises = [];
        draw_progressbar(0, all_size);
        for (let i = 0; i < promise.length; i++) {
            let prom = fs.promises.readFile(dir + files[i]);
            prom.then(() => {
                let h = 0;
                while (h < 1000000000) {
                    h++;
                }
                cur_size += promise[i].value.size;
                draw_progressbar(cur_size, all_size);
            });
            list_pomises.push(prom);
        }
    })
}

function draw_progressbar(cur_size, end_size) {
    let a = cur_size / end_size;

    let string = "";
    let pos;
    for (pos = 0.01; pos < a; pos += 0.01) {
        string += '#';
    }

    for (;pos <= 1; pos += 0.01) {
        string += '-';
    }

    console.log(string);
}
