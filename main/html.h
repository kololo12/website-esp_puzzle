#ifndef HTML_H
#define HTML_H

const char* welcomePage = R"rawliteral(
<html>
<head>
    <meta charset="UTF-8">
    <title>🔎 Tajné Skautské Zprávy</title>
    <style>
        body {
            font-family: 'Courier New', Courier, monospace;
            background: linear-gradient(#0b0c10, #1f2833);
            color: #c5c6c7;
            text-align: center;
            padding: 40px;
            margin: 0;
        }
        h1 {
            color: #66fcf1;
            font-size: 3em;
            margin-bottom: 10px;
        }
        .subtitle {
            font-size: 1.2em;
            color: #45a29e;
            margin-bottom: 40px;
        }
        .theory {
            background-color: #1f2833;
            padding: 20px;
            margin: 20px auto;
            border-radius: 15px;
            width: 90%;
            max-width: 600px;
            box-shadow: 0 0 15px #66fcf1;
            transition: 0.3s;
        }
        .theory:hover {
            transform: scale(1.02);
            box-shadow: 0 0 20px #45a29e;
        }
        h2 {
            color: #66fcf1;
            font-size: 1.5em;
            margin-bottom: 10px;
        }
        p {
            font-size: 1.1em;
            line-height: 1.5;
        }
        form {
            margin-top: 40px;
        }
        .nickname-input {
            padding: 12px;
            width: 260px;
            font-size: 16px;
            border: 2px dashed #f1c40f;
            border-radius: 8px;
            background-color: #0b0c10;
            color: #f1c40f;
            outline: none;
            margin-bottom: 20px;
            box-shadow: 0 0 10px #f1c40f;
        }
        .nickname-input::placeholder {
            color: #f1c40f;
        }
        input[type=text] {
            padding: 12px;
            width: 260px;
            font-size: 16px;
            border: 2px solid #66fcf1;
            border-radius: 8px;
            background-color: #0b0c10;
            color: #c5c6c7;
            outline: none;
            margin: 10px 0;
        }
        input[type=text]::placeholder {
            color: #45a29e;
        }
        input[type=submit] {
            padding: 12px 30px;
            background-color: #45a29e;
            color: #0b0c10;
            border: none;
            border-radius: 8px;
            margin-top: 20px;
            font-size: 16px;
            cursor: pointer;
            transition: background-color 0.3s, color 0.3s;
        }
        input[type=submit]:hover {
            background-color: #66fcf1;
            color: #0b0c10;
        }
        .note {
            font-size: 1em;
            color: #f1c40f;
            margin-top: 20px;
        }
    </style>
</head>
<body>
    <h1>🔎 Tajné Skautské Zprávy</h1>
    <div class="subtitle">Odhal tajemství ukrytá v lesích...</div>

    <div class="theory">
        <h2>Šifra #1: Záhadná zmizení v Černém lese</h2>
        <p>Nikdo nikdy nevysvětlil, proč skauti v roce 1998 náhle zmizeli během noční výpravy...</p>
		<p>50 72 6F 70 61 73 74</p>
    </div>

    <div class="theory">
        <h2>Šifra #2: Tajemné šepoty u Borovic</h2>
        <p>„V noci ticho a ve dne se skrývám, v temnu však vždy najdu cestu. Mám zuby, ale ne jím, ať je den či noc, vždy jsem v pohybu. Nepotřebuji oči, abych věděl, co je kolem. Kdo jsem?“</p>
    </div>

    <div class="theory">
        <h2>Šifra #3: Neviditelný průvodce</h2>
        <p>Říká se, že v určitých nocích skupinu sleduje neviditelný ochránce, který odhání vetřelce. (mimochodem umí čínsky nebo nějak tak...)</p>
		<p>|||---|--|	,	|-	,	||---|-|	,	--||||-|	,	-|-|||	,	|-||	,	-|||-	,	|||-|-  </p>
    </div>

    <form action="/check-password" method="POST">
        <input class="nickname-input" type="text" name="nickname" placeholder="Tvoje přezdívka nebo jméno" required><br>
        <input type="text" name="part1" placeholder="1. část hesla" required><br>
        <input type="text" name="part2" placeholder="2. část hesla" required><br>
        <input type="text" name="part3" placeholder="3. část hesla" required><br>
        <input type="submit" value="Ověřit">
    </form>

    <div class="note">
        <p><strong>Poznámka:</strong> Heslo musí být napsané malými písmeny, bez mezer, háčků a čárek.</p>
    </div>
</body>
</html>
)rawliteral";




const char* successPage = R"rawliteral(
<html>
<head>
    <meta charset="UTF-8">
    <style>
        body { font-family: Arial, sans-serif; background-color: #d0f0c0; text-align: center; padding: 50px; }
        h1 { color: #2e7d32; font-size: 2em; }
        p { color: #555; margin-top: 20px; font-size: 1.2em; }
    </style>
</head>
<body>
    <h1>🎉 Gratuluji! Našel jsi tajemství!</h1>
    <p>Pokračuj dál v objevování!</p>
</body>
</html>
)rawliteral";

const char* wrongPage = R"rawliteral(
<html>
<head>
    <meta charset="UTF-8">
    <style>
        body { font-family: Arial, sans-serif; background-color: #f8d7da; text-align: center; padding: 50px; }
        h1 { color: #c62828; font-size: 2em; }
        p { color: #555; margin-top: 20px; font-size: 1.2em; }
        a { margin-top: 20px; display: inline-block; color: #c62828; text-decoration: underline; }
    </style>
</head>
<body>
    <h1>❌ Špatné heslo!</h1> 
    <p>Zkus to znovu...</p>
    <a href="/">Zpět na hlavní stránku</a>
</body>
</html>
)rawliteral";

const char* adminPageHeader = R"rawliteral(
<html>
<head>
    <meta charset="UTF-8">
    <title>Admin Panel – Tajná hra</title>
    <style>
        body {
            font-family: 'Courier New', Courier, monospace;
            background-color: #0b0c10;
            color: #c5c6c7;
            text-align: center;
            padding: 40px;
        }
        h1 {
            color: #66fcf1;
            margin-bottom: 20px;
        }
        ul {
            list-style-type: none;
            padding: 0;
        }
        li {
            background-color: #1f2833;
            margin: 10px auto;
            padding: 15px;
            border-radius: 10px;
            max-width: 400px;
            box-shadow: 0 0 10px #66fcf1;
        }
        form {
            margin-top: 30px;
        }
        input[type=submit] {
            padding: 10px 20px;
            background-color: #c62828;
            color: white;
            border: none;
            border-radius: 8px;
            cursor: pointer;
            font-size: 16px;
        }
        input[type=submit]:hover {
            background-color: #e53935;
        }
    </style>
</head>
<body>
    <h1>🛡️ Admin Panel</h1>
    <p>Seznam hráčů, kteří dokončili hru:</p>
    <ul>
)rawliteral";

const char* adminPageFooter = R"rawliteral(
    </ul>
    <form action="/logout" method="POST">
        <input type="submit" value="Odhlásit admin">
    </form>
</body>
</html>
)rawliteral";

const char* accessDeniedPage = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>🚫 Přístup zamítnut</title>
    <style>
        body {
            font-family: 'Courier New', Courier, monospace;
            background-color: #2b2b2b;
            color: #ff6b6b;
            text-align: center;
            padding: 50px;
        }
        h1 {
            font-size: 2.5em;
        }
        p {
            font-size: 1.2em;
            margin-top: 20px;
        }
        a {
            display: inline-block;
            margin-top: 30px;
            color: #66fcf1;
            text-decoration: none;
            font-weight: bold;
        }
        a:hover {
            text-decoration: underline;
        }
    </style>
</head>
<body>
    <h1>🚫 Přístup zamítnut</h1>
    <p>Nemáš oprávnění k zobrazení této stránky.<br>
    Tlačítko nebylo stisknuto nebo session vypršela.</p>
    <a href="/">Zpět na hlavní stránku</a>
</body>
</html>
)rawliteral";

#endif // HTML_H
