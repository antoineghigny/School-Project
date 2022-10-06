package com.example.pae;

import javax.validation.constraints.Min;
import javax.validation.constraints.NotNull;

public class Course {
    @NotNull
    String cours;

    @NotNull
    String titre;

    @Min(0)
    int ects;

    public Course(String cours, String titre, int ects) {
        this.cours = cours;
        this.titre = titre;
        this.ects = ects;
    }

    public Course() {
    }

    public String getCours() {
        return cours;
    }

    public String getTitre() {
        return titre;
    }

    public int getEcts() {
        return ects;
    }


    public void setCours(String cours) {
        this.cours = cours;
    }

    public void setTitre(String titre) {
        this.titre = titre;
    }

    public void setEcts(int ects) {
        this.ects = ects;
    }
}
