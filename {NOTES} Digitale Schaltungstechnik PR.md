---
banner: /assets/banner/JKU-Banner.png
banner_y: 0.5
banner_x: 0.5
tags:
  - Bachelor
subject:
  - Digitale Schaltungstechnik
  - PR
semester: WS25
created: 7. August 2025
professor:
  - Patrick Fath
list: false
done:
ects: 3
grade:
type: Frei
---

# Digitale Schaltungstechnik

> [!info] **Klausuren** ✒️
> 

## Praktikum

```dataviewjs
if(dv.current().list) {
    await dv.view("10_tools/dataviewjs/lva_query", {subjectFilter: "Digitale Schaltungstechnik", subjectType: "PR"});
} else {
	dv.paragraph("> [!hint] Enable list in frontmatter to view LVA related notes")
}
```

## Aufgabe 5

![invert_dark|400](../../../_assets/Excalidraw/%7BNOTES%7D%20Digitale%20Schaltungstechnik%20PR%202026-02-01%2002.20.54.excalidraw.svg)
%%[🖋 Edit in Excalidraw](../../../_assets/Excalidraw/%7BNOTES%7D%20Digitale%20Schaltungstechnik%20PR%202026-02-01%2002.20.54.excalidraw.md)%%

![](../../../_assets/Excalidraw/%7BNOTES%7D%20Digitale%20Schaltungstechnik%20PR%202026-02-01%2004.57.43.excalidraw.svg)
%%[🖋 Edit in Excalidraw](../../../_assets/Excalidraw/%7BNOTES%7D%20Digitale%20Schaltungstechnik%20PR%202026-02-01%2004.57.43.excalidraw.md)%%

## Aufgabe 7


Vorbereitung:

- Aufgabe 1: Morse Code Symbole. Siehe Code `tx.ino`
- Aufgabe 2: `tone(pin,freq,duration)`. Siehe Code `tx.ino`
- Aufgabe 3: Widerstände Berechnen

![invert_dark|400](../../../_assets/Excalidraw/2026-01-31-Saturday%202026-01-31%2001.57.51.excalidraw.svg)
%%[🖋 Edit in Excalidraw](../../../_assets/Excalidraw/2026-01-31-Saturday%202026-01-31%2001.57.51.excalidraw.md)%%

Praktikums durchführung:

- Transmitter am Steckbrett Aufbauen: IR-Led, NMOST, R1, R2
- Transmitter Code implementierung (fertig in `tx.ino`)
- Receiver Code implementierung (fertig in `rx.ino`)
- Am TX via serial chars eingeben und senden
- Am RX empfangenen chars via Serial ausgeben
- Oszi bilder
