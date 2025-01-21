# Map-Reduce cu Pthreads: Identificarea Numerelor Perfecte

## Descriere
Acest proiect implementează un program paralel utilizând Pthreads pentru identificarea numerelor mai mari decât 0 care sunt puteri perfecte dintr-un set de fișiere. Programul folosește modelul **Map-Reduce** pentru a paraleliza procesarea fișierelor de intrare și a număra valorile unice pentru fiecare exponent.

## Cerințe
Programul procesează un set de fișiere, identifică numerele care sunt puteri perfecte și le organizează pe exponenți. Fiecare exponent va avea un fișier de ieșire care conține numărul de valori unice identificate.

### Paradigma Map-Reduce
1. **Mapper**: Identifică puterile perfecte din fișierele de intrare și creează liste parțiale pentru fiecare exponent.
2. **Reducer**: Combină listele parțiale și numără valorile unice pentru fiecare exponent, scriind rezultatele într-un fișier de ieșire.

## Structura fișierelor de intrare și ieșire

### Fișier de intrare
Fișierul principal de intrare conține lista fișierelor ce urmează să fie procesate:
```
<număr_fișiere>
<fișier1>
<fișier2>
...
<fișierN>
```

Fiecare fișier din lista de mai sus conține valori numerice:
```
<număr_valori>
<valoare1>
<valoare2>
...
<valoareN>
```

### Fișiere de ieșire
Pentru fiecare exponent `E`, se creează un fișier de ieșire numit `outE.txt`, care conține o singură valoare:
```
<număr_valori_unice>
```

## Instrucțiuni de rulare
Programul se compilează și se rulează astfel:

1. **Compilare:**
   ```bash
   gcc -pthread -o tema1 tema1.c
   ```

2. **Rulare:**
   ```bash
   ./tema1 <număr_mapperi> <număr_reduceri> <fișier_intrare>
   ```

   - `<număr_mapperi>`: Numărul de thread-uri Mapper.
   - `<număr_reduceri>`: Numărul de thread-uri Reducer.
   - `<fișier_intrare>`: Fișierul care conține lista fișierelor de procesat.

### Exemplu de rulare

Fișier de intrare:
```
4
in1.txt
in2.txt
in3.txt
in4.txt
```

Fișiere de procesat:
- `in1.txt`:
  ```
  6
  243
  9
  27
  243
  81
  243
  ```
- `in2.txt`:
  ```
  6
  81
  9
  27
  243
  27
  27
  ```
- `in3.txt`:
  ```
  6
  9
  27
  9
  81
  9
  53
  ```
- `in4.txt`:
  ```
  5
  243
  243
  243
  1
  0
  ```

Comandă:
```bash
./tema1 3 5 test.txt
```

Fișiere de ieșire generate:
- `out2.txt` (pătrate perfecte): `3`
- `out3.txt` (cuburi perfecte): `2`
- `out4.txt`: `2`
- `out5.txt`: `2`
- `out6.txt`: `1`

## Detalii tehnice

1. **Operațiile Map:**
   - Thread-urile Mapper procesează fișierele alocate dinamic.
   - Pentru fiecare valoare din fișier:
     - Se verifică dacă este o putere perfectă a unui exponent (de la 2 până la `<număr_reduceri>`).
     - Valorile sunt salvate în liste parțiale separate pentru fiecare exponent.

2. **Operațiile Reduce:**
   - Fiecare Reducer combină listele parțiale ale unui exponent într-o listă agregată.
   - Se numără valorile unice din lista agregată.
   - Rezultatul este scris într-un fișier de ieșire.

## Observații importante
- **Sincronizare:** Reducerii nu încep execuția decât după finalizarea Mapper-ilor.
- **Alocare dinamică:** Mapper-ii primesc fișiere în mod dinamic pentru echilibrarea încărcării.
- **Validare input:** Programul tratează exclusiv numere întregi pozitive.

## Limitări
- Programul presupune că toate fișierele de intrare conțin date valide.
- Numerele mai mari decât 0 sunt considerate pentru identificarea puterilor perfecte.

## Autori
Acest proiect a fost realizat în cadrul cursului **Algoritmi Paraleli și Distribuiți**.



![image](https://user-images.githubusercontent.com/73692534/220130863-08e4dd70-2aee-4657-9d4d-1ea5f15dcde3.png)
