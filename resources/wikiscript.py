import wikipedia

wikipedia.set_lang("tr")

turkish_cities = [
    "Adana", "Adıyaman", "Afyonkarahisar", "Ağrı", "Amasya", "Ankara", "Antalya", "Artvin",
    "Aydın", "Balıkesir", "Bilecik", "Bingöl", "Bitlis", "Bolu", "Burdur", "Bursa", "Çanakkale",
    "Çankırı", "Çorum", "Denizli", "Diyarbakır", "Edirne", "Elazığ", "Erzincan", "Erzurum",
    "Eskişehir", "Gaziantep", "Giresun", "Gümüşhane", "Hakkari", "Hatay", "Isparta", "Mersin",
    "İstanbul", "İzmir", "Kars", "Kastamonu", "Kayseri", "Kırklareli", "Kırşehir", "Kocaeli",
    "Konya", "Kütahya", "Malatya", "Manisa", "Kahramanmaraş", "Mardin", "Muğla", "Muş", "Nevşehir",
    "Niğde", "Ordu", "Rize", "Sakarya", "Samsun", "Siirt", "Sinop", "Sivas", "Tekirdağ", "Tokat",
    "Trabzon", "Tunceli", "Şanlıurfa", "Uşak", "Van", "Yozgat", "Zonguldak", "Aksaray", "Bayburt",
    "Karaman", "Kırıkkale", "Batman", "Şırnak", "Bartın", "Ardahan", "Iğdır", "Yalova", "Karabük",
    "Kilis", "Osmaniye", "Düzce"
]

#81 Provinces of Türkiye was not enough to obtain a >= 3MB text, so I have added some more cities/provinces that were once part of the Ottoman Empire
former_turkish_provinces = [
    "Atina", "Bağdat", "Belgrad", "Beyrut", "Bükreş", "Cezayir", "Şam",
    "Kahire", "Kerkük", "Kudüs", "Musul", "Saraybosna", "Selanik", "Sofya",
    "Üsküp", "Priştine", "Tiran", "Mostar", "Halep", "Trablusgarp", "Bingazi",
    "Cidde", "Medine", "Tunus", "Marakeş", "Kazablanka", "Gazze",
    "Lefkoşa", "Girne", "Magosa", "Rodos", "Girit", "Batum", "Tiflis"
]

#Some more cities around the world
cities_around_the_world = [
    "Paris", "Berlin", "Londra", "Roma", "Viyana", "Madrid", "Lizbon",
    "Amsterdam", "Brüksel", "Varşova", "Prag", "Budapeşte", "Moskova",
    "Kiev", "Helsinki", "Stockholm", "Oslo", "Kopenhag", "Dublin",
    "Krakow", "Venedik", "Barselona", "Milano", "Münih", "Chicago",
    "New York", "Los Angeles", "Toronto", "Tokyo", "Pekin", "Şangay",
    "Seul", "Bangkok", "Yeni Delhi", "Kuala Lumpur", "Dubai", "Zagreb",
    "Şarm El Şeyh", "Gize", "Abidjan", "Rio de Janeiro", "Porto", "Braga",
    "Granada", "Sevilla", "Valencia", "Bilbao", "Pisa", "Floransa", "Napoli",
    "Palermo", "Bologna", "Köln", "Hamburg", "Frankfurt", "Marsilya",
    "Gdansk", "Rotterdam", "Eindhoven", "Bergen", "Birmingham", "Manchester",
    "Liverpool", "Malmö", "Espoo", "Lviv", "Odessa", "Kazan", "Ufa",
    "Yekaterinburg", "Dubrovnik", "Ostrava", "Bratislava", "Glasgow", "Dundee"

]

def download_and_combine_wiki_text(city_list, filename="cities_wiki.txt"):
    with open(filename, "w", encoding="utf-8") as outfile:
        for city in city_list:
            try:
                page = wikipedia.page(city)
                outfile.write(page.content)
                outfile.write("\n\n")
                print(f"Downloaded and wrote '{city}' to '{filename}' {city_list.index(city)}/{len(city_list)} completed.")
            except wikipedia.exceptions.DisambiguationError as e:
                try:
                    # Try again with "(il)" appended
                    page = wikipedia.page(city + " (il)")
                    outfile.write(page.content)
                    outfile.write("\n\n")
                    print(f"Downloaded and wrote '{city} (il)' to '{filename}' {city_list.index(city)}/{len(city_list)} completed.")
                except wikipedia.exceptions.PageError as e2:
                    print(f"Error downloading page '{city} (il)': {e2}")
            except wikipedia.exceptions.PageError as e:
                print(f"Error downloading page '{city}': {e}")

download_and_combine_wiki_text(turkish_cities + former_turkish_provinces + cities_around_the_world)
