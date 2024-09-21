% Define the integrand as an anonymous function
f = @(x) x + cos(x.^5);

% Set the limits of integration
a = 0;
b = pi;

% Perform the integration using MATLAB's integral function
result = integral(f, a, b);

% Display the result
disp(result);
