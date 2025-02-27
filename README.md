# Pankkiautomaattisovellus/group_12

Tämä projekti on tehty koulutyönä kurssille Ohjelmistokehityksen sovellusprojekti (IN00ED14-3003), jota ohjaavat ja opettavat Pekka Alaluukas sekä Teemu Korpela. Projektissa ovat olleet mukana Emma Takkinen, Erika Turtinen, Tero Asilainen sekä Terhi Wallin.



Lyhyesti tekniikan osasista:

Tietokantana meillä on käytössä MySQL. Tiukan pohdinnan ja opettajan palautteen jälkeen ER-kaaviosta muotoutui seuraavanlainen:

ER model
<img src="ERmodel_Group12.png">

API-rajapinnan toteutimme Node.js/express -tekniikalla. Työnjakona toimi sellainen, että jokainen opiskelija toteutti CRUD-operaatiot omaan tietokantatauluunsa.


Työpöytäsovelluksen loimme QtCreatorilla. Suunnitelma voisi näyttää kutakuinkin seuraavalta:

Kuva:
<img src="KoulutyöREADME.png">

## Lisätoiminnot:

- Tumma/Vaalea teema
    -> Käyttäjä pystyy itse valitsemaan tumman tai vaalean teeman väliltä.

- Kielivalinta
    -> Käyttäjä voi valita käyttääkö suomen vai englannin kieltä.

- Siirto
    -> Käyttäjä voi siirtää rahaa omien tilien välillä.

- Maksu
    -> Käyttäjä voi suorittaa maksun valitsemalleen tilille.

- Ajastin
    -> Jos käyttäjä ei paina mitään määritetyn ajan kuluessa, käyttäjä siirtyy edelliseen ikkunaan ja lopulta myös kirjataan ulos sovelluksesta.

## Työnjako

Emma
- Saldokysely, käyttäjätiedot, account-taulun CRUD-toiminnot, tumma teema, sovelluksen suunnitelma...

Erika
- Tilitapahtumat, maksu- ja nosto-toimintojen yhdistäminen Node.js:ään ja tietokantaan, tietokantaproseduurit, transaction-taulun ja account_user-taulun CRUD-toiminnot...

Terhi
- User-taulun CRUD-toiminnot, maksu- ja nosto-toimintojen käyttöliittymät, kielivalinta ja käännökset...

Tero
- Card- ja card_account-taulujen CRUD-toiminnot, kirjautuminen, siirto-ominaisuus, vaalea teema, graafisen ulkoasun suunnitelu ja toteutus, tietokannan ja API:n siirtäminen Linux-palvelimelle...

Projektiin liittyvät dokumentit ja UML-kaaviot olemme tehneet ryhmän kesken.