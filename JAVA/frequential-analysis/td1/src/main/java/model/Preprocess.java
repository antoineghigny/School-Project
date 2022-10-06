package model;

import java.text.Normalizer;

public class Preprocess 
{
    /**
     * Sanitize the given string to only lowercase alphabetic characters.
     * All characters are converted to lowercase.
     * Characters with diacritics are converted to the corresponding
     * alphabetic character.
     * All remaining non-alphabetic characters are removed.
     *
     * @param str string to sanitize.
     * @return a string made only of alphabetic [a-z] characters.
     */
    public static String sanitizeToAlpha(String str) 
    {
        return Normalizer
                .normalize(str.toLowerCase(), Normalizer.Form.NFD)
                .replaceAll("[^a-z]", "");
    }   
}

