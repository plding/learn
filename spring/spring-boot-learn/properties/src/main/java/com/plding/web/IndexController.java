package com.plding.web;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class IndexController {

    @Value("${app.name}")
    private String name;

    @GetMapping("/")
    public String index() {
        return name;
    }
}
