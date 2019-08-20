module pwm_selector(in, sw0, sw1, pwm_1, pwm_r1, pwm_2, pwm_r2);
    input in, sw0, sw1;
    output pwm_1, pwm_r1, pwm_2, pwm_r2;

    wire pwm_1_R, pwm_1_L, pwm_r1_R, pwm_r1_L, pwm_2_R, pwm_2_L, pwm_r2_R, pwm_r2_L;

    wire yukiko = 1'b0;

    stepping_controller_R stepping_controller_R(in, pwm_1_R, pwm_r1_R, pwm_2_R, pwm_r2_R);
    stepping_controller_L stepping_controller_L(in, pwm_1_L, pwm_r1_L, pwm_2_L, pwm_r2_L);

    assign yukiko = selector(sw0, sw1);
    assign {pwm_1, pwm_r1, pwm_2, pwm_r2} = yukiko ? {pwm_1_R, pwm_r1_R, pwm_2_R, pwm_r2_R} : {pwm_1_L, pwm_r1_L, pwm_2_L, pwm_r2_L};

    function selector(input sw0, sw1);
        if(sw0 == 1) begin
            selector = 1'b1;
        end else if(sw1 == 1) begin
            selector = 1'b0;
        end else begin
            selector = yukiko;
        end
    endfunction

/*
    always @(posedge sw0) begin
        yukiko = 1'b1;
    end

    always @(posedge sw1) begin
        yukiko = 1'b0;
    end
*/
endmodule
