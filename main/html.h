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
        input[type=text] {
            padding: 12px;
            width: 260px;
            font-size: 16px;
            border: 2px solid #66fcf1;
            border-radius: 8px;
            background-color: #0b0c10;
            color: #c5c6c7;
            outline: none;
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
    </style>
</head>
<body>
    <h1>🔎 Tajné Skautské Zprávy</h1>
    <div class="subtitle">Odhal tajemství ukrytá v lesích...</div>

    <div class="theory">
        <h2>Teorie #1: Záhadná zmizení v Černém lese</h2>
        <p>Nikdo nikdy nevysvětlil, proč skauti v roce 1998 náhle zmizeli během noční výpravy...</p>
    </div>

    <div class="theory">
        <h2>Teorie #2: Tajemné šepoty u Borovic</h2>
        <p>Je slyšet šepot v korunách stromů... některé zprávy mluví o starodávném rituálu skautských strážců.</p>
    </div>

    <div class="theory">
        <h2>Teorie #3: Neviditelný průvodce</h2>
        <p>Říká se, že v určitých nocích skupinu sleduje neviditelný ochránce, který odhání vetřelce.</p>
    </div>

    <form action="/check-password" method="POST">
        <input type="text" name="password" placeholder="Zadej tajné heslo" required>
        <br>
        <input type="submit" value="Ověřit">
    </form>
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

#endif // HTML_H
