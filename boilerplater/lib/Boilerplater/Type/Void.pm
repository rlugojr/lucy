use strict;
use warnings;

package Boilerplater::Type::Void;
use base qw( Boilerplater::Type );
use Boilerplater::Util qw( verify_args );
use Scalar::Util qw( blessed );
use Carp;

our %new_PARAMS = ( 
    const     => undef,
    specifier => 'void', 
);

sub new {
    my ( $either, %args ) = @_;
    verify_args( \%new_PARAMS, %args ) or confess $@;
    my $c_string = $args{const} ? "const void" : "void";
    return $either->SUPER::new(
        %new_PARAMS,
        %args,
        specifier => 'void',
        c_string  => $c_string
    );
}

sub is_void {1}

sub equals {
    my ( $self, $other ) = @_;
    return 0 unless blessed($other);
    return 0 unless $other->isa(__PACKAGE__);
    return 1;
}

1;

__END__

=head1 NAME

Boilerplater::Type::Void - The void Type.

=head1 DESCRIPTION

Boilerplater::Type::Void is used to represent a void return type.  It is also
used in conjuction with with L<Boilerplater::Type::Composite> to support the
C<void*> opaque pointer type.

=head1 METHODS

=head2 new

    my $type = Boilerplater::Type::Void->new(
        specifier => 'void',    # default: void
        const     => 1,         # default: undef
    );

=over

=item * B<specifier> - Must be "void" if supplied.

=item * B<const> - Should be true if the type is const.  (Useful in the
context of C<const void*>).

=back

=head1 COPYRIGHT AND LICENSE

    /**
     * Copyright 2009 The Apache Software Foundation
     *
     * Licensed under the Apache License, Version 2.0 (the "License");
     * you may not use this file except in compliance with the License.
     * You may obtain a copy of the License at
     *
     *     http://www.apache.org/licenses/LICENSE-2.0
     *
     * Unless required by applicable law or agreed to in writing, software
     * distributed under the License is distributed on an "AS IS" BASIS,
     * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
     * implied.  See the License for the specific language governing
     * permissions and limitations under the License.
     */

=cut

