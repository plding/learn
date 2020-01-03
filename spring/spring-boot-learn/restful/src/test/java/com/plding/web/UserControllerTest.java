package com.plding.web;

import static org.hamcrest.Matchers.*;
import static org.mockito.Mockito.*;
import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.*;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.*;
import static org.springframework.test.web.servlet.setup.MockMvcBuilders.*;

import org.junit.Test;
import org.springframework.test.web.servlet.MockMvc;

public class UserControllerTest {

    @Test
    public void test() throws Exception {
        MockMvc mvc = standaloneSetup(new UserController()).build();

        mvc.perform(get("/users"))
           .andExpect(content().string(equalTo("[]")));

        mvc.perform(post("/users").param("id", "1").param("name", "plding").param("age", "30"))
           .andExpect(content().string(equalTo("success")));

        mvc.perform(get("/users"))
           .andExpect(content().string(equalTo("[{\"id\":1,\"name\":\"plding\",\"age\":30}]")));

        mvc.perform(delete("/users/1"))
           .andExpect(content().string(equalTo("success")));

        mvc.perform(get("/users"))
           .andExpect(content().string(equalTo("[]")));
    }
}
