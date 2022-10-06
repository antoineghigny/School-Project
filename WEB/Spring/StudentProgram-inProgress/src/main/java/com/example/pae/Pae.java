package com.example.pae;

import java.util.ArrayList;
import java.util.List;

import org.springframework.stereotype.Service;

@Service
public class Pae {
    
    // crée constructeur
    public List<Course> courses = new ArrayList<>();

    public Pae() {
        courses.add(new Course("INT1", "Introduction I", 10));
        courses.add(new Course("MAT1", "Mathématique II", 3));
        courses.add(new Course("CAI1", "Anglais I", 2));
        courses.add(new Course("DEV1", "Développement I", 10));
        courses.add(new Course("DEV2", "Développement II", 10));
        courses.add(new Course("WEBG2", "Développement web I", 5));
    }

    public List<Course> getCourses() {
        return courses;
    }

    public void addCourse(Course cours) {
        courses.add(cours);
    }
}
