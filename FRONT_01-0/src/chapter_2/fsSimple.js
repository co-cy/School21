const fs = require("fs");

const readAndWriteCallbackHell = () => {
  fs.readFile("files/fsSimple/file1.txt", (err, data) => {
    if (err)
      throw err;
    fs.writeFile("files/fsSimple/file2.txt", data, (err) => {
      if (err)
        throw err;
      console.log("Save!");
    });
  })
};

const readAndWritePromises = () => {
  let promise = fs.promises.readFile("files/fsSimple/file1.txt");
  promise.then((res) => {
    fs.promises.writeFile("files/fsSimple/file2.txt", res);
  })
};

const readAndWriteAsyncAwait = async () => {
  let res = await fs.promises.readFile("files/fsSimple/file1.txt");
  fs.promises.writeFile("files/fsSimple/file2.txt", res);
};
