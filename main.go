package main

import (
	"bufio"
	"io"
	"math/rand"
	"net/http"
	"os"
	"strconv"
)

const IMG_NUM int = 10
const srcRoot string = "root/"

func main() {
	http.HandleFunc("/", mainHandler)
	http.HandleFunc("/favicon.ico", webIconHandler)
	http.HandleFunc("/funny_box.html", funnyHandler)
	http.HandleFunc("/random_funny", randomFunnyHandler)
	http.ListenAndServe(":8888", nil)
}

func mainHandler(w http.ResponseWriter, r *http.Request) {
	f, err := os.OpenFile(srcRoot+"index.html", os.O_RDONLY, 0666)
	if err != nil {
		w.WriteHeader(404)
		return
	}
	defer f.Close()
	io.Copy(w, f)
}

func webIconHandler(w http.ResponseWriter, r *http.Request) {
	w.WriteHeader(404)
}

func funnyHandler(w http.ResponseWriter, r *http.Request) {
	f, err := os.OpenFile(srcRoot+"funny_box.html", os.O_RDONLY, 0666)
	if err != nil {
		w.WriteHeader(404)
		return
	}
	defer f.Close()
	io.Copy(w, f)
}

func randomFunnyHandler(w http.ResponseWriter, r *http.Request) {
	fileNo := rand.Int() % 10
	f, err := os.OpenFile(srcRoot+"funny_mystery_box/"+strconv.Itoa(fileNo)+"png", os.O_RDONLY, 0666)
	if err != nil {
		f, err = os.OpenFile(srcRoot+"funny_mystery_box/"+strconv.Itoa(fileNo)+".jpg", os.O_RDONLY, 0666)
		if err != nil {
			w.WriteHeader(404)
			return
		}
	}
	defer f.Close()
	buf := bufio.NewReader(f)
	io.Copy(w, buf)
}
