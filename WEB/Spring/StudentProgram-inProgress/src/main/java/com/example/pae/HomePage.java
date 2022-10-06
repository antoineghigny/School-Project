package com.example.pae;

import java.lang.ProcessBuilder.Redirect;

import javax.validation.Valid;

import org.apache.catalina.User;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.validation.Errors;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@Controller
public class HomePage {

    @Autowired
    private Pae pae;

    @GetMapping("/")
    public String showCourses(Model model) {
        return "home";
    }

    @GetMapping("/courses")
    public String showIndex(Model model) {
        Course course = new Course();
        model.addAttribute("course", course);
        model.addAttribute("courses", pae.getCourses());
        return "course";
    }

    @GetMapping("/course")
    public String showCourses(@RequestParam String coursId, Model model) {
        model.addAttribute("coursId", coursId);
        return "explaination";
    }

    @PostMapping("/urlCtrl")
    public String doSomething(@Valid Course course, Errors errors, Model model) {
        model.addAttribute("courses", pae.getCourses());

        if (errors.hasErrors()) {
            return "course";
        } else {
            pae.addCourse(course);
            return "course";
        }

    }
}