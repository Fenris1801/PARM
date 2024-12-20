import itertools

# Paramètres de l'ALU
BIT_WIDTH = 4  # Nombre de bits des entrées (modifiez selon votre ALU)
OPERATIONS = ["ADD", "SUB", "AND", "OR", "XOR", "CMP"]  # Types d'opérations
FLAGS = ["Z", "C", "V", "N"]  # Flags attendus

# Génération de toutes les combinaisons possibles pour A et B
values = [bin(i)[2:].zfill(BIT_WIDTH) for i in range(2 ** BIT_WIDTH)]

# Création des vecteurs de test
test_vectors = []
for op in OPERATIONS:
    for a, b in itertools.product(values, repeat=2):
        test_vectors.append({
            "A": a,
            "B": b,
            "Operation": op,
        })

# Écriture des vecteurs dans un fichier
with open("alu_test_vectors.txt", "w") as f:
    f.write("A\tB\tOperation\tExpected_Result\tFlags\n")
    for vector in test_vectors:
        # Calculez les résultats et flags attendus (simulé ou basé sur votre ALU)
        expected_result = "XXXX"  # Remplacez par un calcul réel si nécessaire
        expected_flags = "".join(["0"] * len(FLAGS))  # Exemple : pas de flag activé
        f.write(f"{vector['A']}\t{vector['B']}\t{vector['Operation']}\t{expected_result}\t{expected_flags}\n")

print("Vecteurs de test générés dans 'alu_test_vectors.txt'.")
