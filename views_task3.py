from django.shortcuts import render
from django.http import HttpResponse
import requests
import json

# Create your views here.
def type(request):
    url = "https://pokeapi.co/api/v2/type"
    response = requests.get(url)
    text = json.loads(response.text)['results']
    type_names = "The types of pokemon are: "
    i = 1
    for line in text:
        type_names = type_names + "\n" + f"{i}." + line['name']
        i += 1
    if response.status_code == 200:
        return HttpResponse(type_names, content_type = "text/plain")
    return HttpResponse("An error ocurred while loading all types.")

# Bonus task
def info(request):
    url = "https://pokeapi.co/api/v2/type"
    response = requests.get(url)
    text = json.loads(response.text)['results']
    type_names = "The types of pokemon are: "
    i = 1
    for line in text:
        type_names = type_names + "\n" + f"{i}." + line['name']
        i += 1
    type_names += "\n\n"
    text_1 = json.loads(response.text)['results']
    j = 1
    # n for new and cmp for complete info.
    pokemons = ""
    for line_1 in text_1:    
        nresponse = requests.get(line_1['url'])
        moves_cmp = json.loads(nresponse.text)['moves']
        pokemons += f"Type {j}: {text_1[j - 1]['name']}\n    Moves are:"
        for move in moves_cmp:
            pokemons += "\n" + "\t" + move['name']
        pokemons += "\n\n"
        pokemon_cmp = json.loads(nresponse.text)['pokemon']
        pokemons += "    Pokemons of this type are:"
        for pokemon in pokemon_cmp:
            pokemons += "\n" + "\t" + pokemon['pokemon']['name']
        pokemons += "\n\n"
        j += 1
    final = f"{type_names}{pokemons}"    
    if response.status_code == 200:
        return HttpResponse(final, content_type = "text/plain")
    return HttpResponse("An error ocurred while loading all types.")

# Task 3
def names(request, name):
    url = "https://pokeapi.co/api/v2/type"
    response_1 = requests.get(url)
    text = json.loads(response_1.text)['results']
    url_1 = ""
    for line in text:
        if name == line['name']:
            url_1 += line['url']
            break
        else:
            continue
    nresponse_1 = requests.get(url_1)
    text_1 = json.loads(nresponse_1.text)['pokemon']
    pokemons_1 = f"Pokemons of type '{name}' are:"
    k = 1
    for line in text_1:
        pokemons_1 += "\n" + "    " + f"{k}." + line['pokemon']['name']
        k += 1
    if response_1.status_code == 200 and nresponse_1.status_code == 200:
        return HttpResponse(pokemons_1, content_type = "text/plain")
    return HttpResponse("An error ocurred while loading content.")
    