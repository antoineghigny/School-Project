package com.example.pae.scope;

import lombok.Data;

@Data
public class IDGenerator {

    private static int count = 0;
    private int id;

    public IDGenerator() {
        this.id = ++count;
    }

    public int getIdGen(){
        return id;
    }
}