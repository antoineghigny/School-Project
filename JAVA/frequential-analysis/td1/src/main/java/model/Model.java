package model;

import java.util.*;

public class Model {

    /**
     * Transforms the key to match the length of the text to encode/decode.
     * For example, if the key is "K" and the text is of size 5, the key is
     * transformed into "KKKKK".
     * If the key is "AUTO" and the text is of size 7,
     * the key is transformed into "AUTOAUT".
     *
     * @param str the text to encode/decode
     * @param key the key to transform
     * @return The transformed key
     */
    private static String generateKey(String str, String key) {
        int x = str.length();
        StringBuilder keyBuilder = new StringBuilder(key);

        int i = 0;
        while (true) {
            if (x == i) {
                i = 0;
            }
            if (keyBuilder.length() == str.length()) {
                break;
            }
            keyBuilder.append(keyBuilder.charAt(i));
            i++;
        }
        key = keyBuilder.toString();
        return key;
    }

    /**
     * Encode a text using a key.
     * If the method is CAESAR, the key is of length 1.
     * If the method is VIGENERE, the key is of variable length.
     *
     * @param str the text to encode
     * @param key the key used
     * @param method CAESAR OR VIGENERE
     * @return The encoded text
     */
    private static String cypher(String str, String key, String method) {
        StringBuilder orig_text = new StringBuilder();
        for (int i = 0; i < str.length(); i++) {
            int x;
            if (method.equals("VIGENERE")) {
                x = (str.charAt(i) +
                        key.charAt(i) + 26) % 26;
                x += 'A';

            } else {
                x = (str.charAt(i) + Integer.parseInt(key));
                if (x > 90) {
                    x = x - 90 + 64;
                }
            }
            orig_text.append((char) (x));
        }
        return orig_text.toString();
    }

    /**
     * Facade for the encoding algorithm.
     *
     * @param text the text to encode
     * @param key the key used
     * @param method CAESAR OR VIGENERE
     * @return The encoded text
     */
    public String cypherFacade(String text, String key, String method) {
        String keyword;
        if (method.equalsIgnoreCase("VIGENERE")) {
            keyword = generateKey(text, key);
        } else {
            keyword = key;
        }
        return cypher(text, keyword, method);
    }


    /**
     * Decode a text using a key.
     * If the method is CAESAR, the key is of length 1.
     * If the method is VIGENERE, the key is of variable length.
     *
     * @param cypherText the text to decode
     * @param key the key used
     * @param method CAESAR OR VIGENERE
     * @return The decoded text
     */
    private static String decypher(String cypherText, String key, String method) {
        StringBuilder orig_text = new StringBuilder();
        for (int i = 0; i < cypherText.length(); i++) {
            int x;
            if (method.equals("VIGENERE")) {
                x = (cypherText.charAt(i) -
                        key.charAt(i) + 26) % 26;
                x += 'A';
            } else {
                int a = (int) cypherText.charAt(i);
                x = (cypherText.charAt(i) - (key.charAt(0) - 65));
                if (x < 65) {
                    x = 90 - (64 - x);
                }
            }
            orig_text.append((char) (x));
        }
        return orig_text.toString();
    }


    /**
     * Facade for the decoding algorithm.
     *
     * @param text the text to decode
     * @param key the used key
     * @param method CAESAR OR VIGENERE
     * @return The decoded text
     */
    public String decypherFacade(String text, String key, String method) {
        if (method.equals("VIGENERE")) {
            String keyword = generateKey(text, key);
            return decypher(text, keyword, method);
        } else {
            char keyword = (char) ('A' + Integer.parseInt(key));
            return decypher(text, String.valueOf(keyword), method);
        }
    }

    /**
     * Count and add in a table the number of times each letter is present in the encrypted sentence.
     *
     * @param alphabet  Letters of the alphabet
     * @param encrypted The encrypted sentence
     * @return An array containing the number of times each letter is present.
     */
    private int[] nbTimes(String alphabet, String encrypted) {
        int[] counterArray = new int[26];
        for (int i = 0; i < encrypted.length(); i++) {
            for (int j = 0; j < alphabet.length(); j++) {
                if (encrypted.charAt(i) == alphabet.charAt(j)) {
                    counterArray[j]++;
                }
            }
        }
        return counterArray;
    }

    /**
     * This algorithm will determine the shift used for each substring
     * of the key size. We count for each sub-string the number of each letter
     * present and we add it in a table. Each letter appearance frequency
     * will be compared with its theoretical frequency. The goal will be to
     * get as close as possible to this frequency by increasing the shift each time.
     *
     * @param encrypted The encrypted sentence
     * @return The offset of each index from the size of the key.
     */
    private int calculateOffset(String encrypted) {
        double[] letterFrequencies = {8.34, 1.54, 2.73, 4.14, 12.60, 2.03, 1.92, 6.11, 6.71, 0.23, 0.87, 4.24, 2.53, 6.8, 7.7, 1.66, 0.09, 5.68, 6.11, 9.37, 2.85, 1.06, 2.34, 0.2, 2.04, 0.06};
        String alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        int lengthEncryptedText = encrypted.length();
        double[] m = {0, 100};

        for (int i = 0; i < 26; i++) {

            double diff = 0;
            for (int a = 0; a < 26; a++) {
                int[] count = nbTimes(alphabet, encrypted);
                int b = 100 * count[a] / lengthEncryptedText;
                diff += Math.abs(b - letterFrequencies[a]);
            }
            if (diff < m[1]) {
                m[0] = i;
                m[1] = diff;
            }
            encrypted = decypherFacade(encrypted, Integer.toString(1), "CAESAR");
        }
        return (int) m[0];
    }

    private double sumLetter(double nb) {
        return nb * (nb - 1);
    }

    private static String sliceArray(String string, int startIndex, int pas) {
        StringBuilder stringBuilder = new StringBuilder();
        for (int i = startIndex; i < string.length(); i += pas) {
            stringBuilder.append(string.charAt(i));
        }
        return stringBuilder.toString();
    }

    /**
     * The encrypted text is split according to the key. We count for each sub-string
     * the number of each letter present and we add it in a table. The index is then
     * calculated as the mean of the coincidence indices and returned. As long as this
     * is smaller than the theoretical coincidence index of the letters, we increase
     * the size of the key and start again.
     *
     * @param encrypted The encrypted sentence
     * @param pas       Represents the key size.
     * @return The offset of the current text taking into account that the step would be the size of the key.
     */
    private double calculateIc(String encrypted, int pas) {
        List<Double> list = new ArrayList<>();
        for (int i = 0; i < pas; i++) {
            int[] nbLetter = new int[26];
            int counter = 0;
            String s = sliceArray(encrypted, i, pas);

            for (; counter < s.length(); counter++) {
                char lettre = s.charAt(counter);
                nbLetter[(int) lettre - 65] += 1;
            }
            double sommeLettres = 0;
            for (int k : nbLetter) {
                sommeLettres += sumLetter(k); //
            }
            double sousGroupe = 0;
            for (int k : nbLetter) {
                sousGroupe += k; //
            }
            sommeLettres = sommeLettres / sumLetter(sousGroupe - pas);  // somme des indices de coindidence / nombre de lettres
            list.add(sommeLettres);
        }
        double sum = 0;
        for (Double aDouble : list) {
            sum += aDouble;
        }
        return sum / list.size();
    }

    /**
     * As long as the offset found is smaller than the index of coincidence of the letters in English, we increase the step
     * and we call the function calculerIc again.
     *
     * @param encrypted The encrypted sentence
     * @return The size of the key
     */
    private int decrypt(String encrypted) {
        double plancher = 0.065;
        int pas = 1;
        while (calculateIc(encrypted, pas) < plancher) {
            pas += 1;
        }
        return pas;
    }

    /**
     * Create a list of substrings of the size of the key. For each index block of this block,
     * returns the shift used. Once each shift is found, the key found is then
     * revealed and therefore calls the method to decypher a text knowing the size of the key.
     *
     * @param encrypted The encrypted sentence
     * @return the text revealed.
     */
    public String crack(String encrypted) {
        int findKeyLength = decrypt(encrypted);

        List<String> list = new ArrayList<>();
        for (int i = 0; i < findKeyLength; i++) {
            list.add(sliceArray(encrypted, i, findKeyLength));
        }
        StringBuilder key = new StringBuilder();
        for (String s : list) {
            char keyword = (char) ('A' + calculateOffset(s));
            key.append(keyword);
        }
        key = new StringBuilder(generateKey(encrypted, key.toString()));
        return decypher(encrypted, key.toString(), "VIGENERE");
    }
}
