from jinja2 import Template, Environment, FileSystemLoader
import os, re, glob, click
from pathlib import Path


@click.command()
@click.option("--to", "-o", default="./template.cpp")
#@click.option("--to", "-o", default="../b.cpp")
# @click.option("--to", "-o", default="template.cpp")
@click.option("--encode", default="utf-8")
def rend(to, encode):
    env = Environment(loader=FileSystemLoader("./", encoding=encode))
    tmpl = env.get_template("./template.hpp.j2")

    path = Path("./")
    # files = sorted([p for p in path.glob("./*/*.*") if re.search("/*\.(cpp|c|cc|cxx|hpp|h|hh|hxx)", str(p))])
    files = [
        "template/fn.hpp",
        "template/type.hpp",
        "io/fastio.hpp",
        "template/debug.hpp",
        "template/constant.hpp",
        "template/def.hpp",
        "math/modint.hpp"
    ]
    #print(files)

    files_data = []

    for s in files:
        s = str(s)
        print("reading " + s.replace('\\', '/') + "...  ", end="")
        with open(s, 'r', encoding=encode) as f:
            m = {}
            m["name"] = s.replace('\\', '/')
            m["data"] = f.read()
            files_data.append(m)
        print("done")

    rendered_s = tmpl.render(files_data=files_data)

    with open(to, 'w', encoding=encode) as f:
        f.write(rendered_s)


def main():
    rend()


if __name__ == "__main__":
    main()
