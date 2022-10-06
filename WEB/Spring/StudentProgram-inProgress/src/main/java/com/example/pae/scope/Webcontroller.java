package com.example.pae.scope;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;

import org.springframework.ui.Model;

@Controller
public class Webcontroller {
    @Autowired
    IDGenerator requestBean;

    @Autowired
    IDGenerator sessionBean;

    @Autowired
    IDGenerator singletonBean;

    @Autowired
    IDGenerator defaultBean;

    @GetMapping("/index")
    public String test(Model model) {
        model.addAttribute("requestBean", requestBean.getIdGen());
        model.addAttribute("sessionBean", sessionBean.getIdGen());
        model.addAttribute("singletonBean", singletonBean.getIdGen());
        model.addAttribute("defaultBean", defaultBean.getIdGen());
        model.addAttribute("coursId", 23);

        return "index";
    }
}
