package com.plding.web;

import com.plding.model.User;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/users")
public class UserController {

    static Map<Long, User> users = Collections.synchronizedMap(new HashMap<Long, User>());

    @GetMapping
    public List<User> users() {
        return new ArrayList<User>(users.values());
    }

    @PostMapping
    public String create(@ModelAttribute User user) {
        users.put(user.getId(), user);
        return "success";
    }

    @GetMapping("/{id}")
    public User get(@PathVariable long id) {
        return users.get(id);
    }

    @PutMapping("/{id}")
    public String update(@PathVariable long id, @ModelAttribute User user) {
        users.put(id, user);
        return "success";
    }

    @DeleteMapping("/{id}")
    public String deleteUser(@PathVariable long id) {
        users.remove(id);
        return "success";
    }
}
